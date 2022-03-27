/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/27 13:36:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "expand_str.h"
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include "linked_list.h"
#include "parsing.h"
#include "tokenizer.h"
#include <asm-generic/errno-base.h>
#include <signal.h>
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

static int	treat_infile(struct s_list *infile, int r_pipe)
{
	int			fdin;
	struct s_io	*tmp;

	fdin = -1;
	while (infile)
	{
		tmp = (struct s_io *)infile->content;
		if (tmp->type != APPINFILE)
		{
			if (r_pipe != -1)
			{
				close(r_pipe);
				r_pipe = -1;
			}
			if (fdin != -1)
				close(fdin);
			fdin = open(tmp->file, O_RDONLY | O_CLOEXEC);
		}
		infile = infile->next;
	}
	if (fdin == -1)
		fdin = r_pipe;
	return (fdin);
}

static void	exec_child(struct s_program *programs, struct s_program **first_p,
		struct s_exec *exec)
{
	char				**envp;
	char				*path;
	char *const			*argv;

	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGINT, SIG_DFL);
	expand_program(programs);
	path = check_path(programs->name);
	argv = gen_argv(programs->params, programs->name);
	envp = gen_envp();
	clear_fds_on_programs(*first_p);
	close(exec->tmpin);
	close(exec->tmpout);
	close(exec->fdin);
	if (path)
		execve(path, argv, envp);
	else
		print_msg_command_not_found(programs->name);
	free(path);
	free((void *)argv);
	delete_envp(envp);
	destroy_programs(first_p);
	destroy_hashtbl();
	exit(127);
}

static int	setup_to_exec(struct s_program *programs, struct s_exec *executor)
{
	if (programs->infile)
		executor->fdin = treat_infile(programs->infile, programs->h_pipe[0]);
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
	struct s_exec		exec;
	struct s_program	*tmp;

	setup_signal(SIGINT, handler_exec);
	exec.tmpin = dup(STDIN_FILENO);
	exec.tmpout = dup(STDOUT_FILENO);
	if (NOT programs->infile)
		exec.fdin = dup(exec.tmpin);
	tmp = programs;
	while (programs)
	{
		if (setup_to_exec(programs, &exec))
			return (exit_errno(exec.tmpin, exec.tmpout));
		if (programs->name)
		{
			programs->pid = fork();
			if (programs->pid == 0)
				exec_child(programs, &tmp, &exec);
		}
		programs = programs->next;
	}
	reset_stdin_stdout(exec.tmpin, exec.tmpout);
	return (insert_hashtbl("?", ft_itoa(wait_all(tmp))), 0);
}
