/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/23 13:28:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_str.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include "linked_list.h"
#include "parsing.h"
#include "tokenizer.h"
#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "utils_exec.h"
#include "error.h"

static int	treat_outfile(struct s_list *outfile)
{
	int			fdout;
	struct s_io	*tmp;

	while (outfile)
	{
		tmp = (struct s_io *)outfile->content;
		fdout = open(tmp->file, O_WRONLY | O_APPEND * (tmp->type == APPOUTFILE)
				| O_CREAT | O_CLOEXEC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
		outfile = outfile->next;
		if (outfile)
			close(fdout);
	}
	return (fdout);
}

static int	treat_infile(struct s_list *infile)
{
	int			fdin;
	struct s_io	*tmp;

	while (infile)
	{
		tmp = (struct s_io *)infile->content;
		if (tmp->type == APPINFILE)
		{
			fdin = heredoc(tmp);
			if (infile->next)
				close(fdin);
		}
		infile = infile->next;
	}
	if (tmp->type != APPINFILE)
		fdin = open(tmp->file, O_RDONLY | O_CLOEXEC);
	return (fdin);
}

static void	exec_child(struct s_program *programs, struct s_program **first_p)
{
	char		**envp;
	char		*path;
	char *const	*argv;

	expand_program(programs);
	path = check_path(programs->name);
	argv = gen_argv(programs->params, programs->name);
	envp = gen_envp();
	garbage_collector(3);
	if (path)
		execve(path, argv, envp);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(programs->name, 2);
		ft_putchar_fd(':', 2);
		ft_putendl_fd(" command not found", 2);
	}
	free((void *)argv);
	free(path);
	delete_envp(envp);
	destroy_hashtbl();
	destroy_programs(first_p);
	exit(errno);
}

static int	setup_to_exec(struct s_program *programs, struct s_exec *executor)
{
	if (programs->infile)
		executor->fdin = treat_infile(programs->infile);
	if (executor->fdin < 0)
		return (exit_errno(executor->tmpin, executor->tmpout));
	dup2(executor->fdin, STDIN_FILENO);
	close(executor->fdin);
	if (programs->next == NULL)
	{
		if (programs->outfile)
			executor->fdout = treat_outfile(programs->outfile);
		else
			executor->fdout = dup(executor->tmpout);
		if (executor->fdout < 0)
			return (exit_errno(executor->tmpin, executor->tmpout));
	}
	else
	{
		if (pipe(executor->_pipe) == -1)
			return (exit_errno(executor->tmpin, executor->tmpout));
		executor->fdin = executor->_pipe[0];
		executor->fdout = executor->_pipe[1];
	}
	dup2(executor->fdout, STDOUT_FILENO);
	close(executor->fdout);
	return (0);
}

int	executor(struct s_program *programs)
{
	int					exit_status;
	struct s_exec		executor;
	struct s_program	*tmp;

	executor.tmpin = dup(STDIN_FILENO);
	executor.tmpout = dup(STDOUT_FILENO);
	if (NOT programs->infile)
		executor.fdin = dup(executor.tmpin);
	tmp = programs;
	while (programs)
	{
		if (setup_to_exec(programs, &executor))
			return (exit_errno(executor.tmpin, executor.tmpout));
		if (programs->name)
		{
			programs->pid = fork();
			if (programs->pid == 0)
				exec_child(programs, &tmp);
		}
		programs = programs->next;
	}
	reset_stdin_stdout(executor.tmpin, executor.tmpout);
	exit_status = wait_all(tmp);
	return (insert_hashtbl("?", ft_itoa(exit_status)), 0);
}
