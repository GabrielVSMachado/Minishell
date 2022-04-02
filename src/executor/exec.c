/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 15:43:52 by gvitor-s         ###   ########.fr       */
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
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
				| O_TRUNC * (tmp->type != APPOUTFILE) | O_CREAT | O_CLOEXEC,
				S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
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
	int			save_errno;

	fdin = r_pipe;
	while (infile)
	{
		tmp = (struct s_io *)infile->content;
		if (tmp->type != APPINFILE)
		{
			if (r_pipe != -1)
			{
				save_errno = errno;
				(void)close(r_pipe);
				errno = save_errno;
				r_pipe = -1;
			}
			if (fdin != r_pipe)
				close(fdin);
			fdin = open(tmp->file, O_RDONLY | O_CLOEXEC);
		}
		infile = infile->next;
	}
	return (fdin);
}

static void	exec_child(struct s_program *programs, struct s_program **fstp,
		struct s_exec *exec)
{
	char				**envp;
	char *const			*argv;
	int					exit_code;

	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGINT, SIG_DFL);
	clear_fds_on_child(*fstp, exec);
	argv = gen_argv(programs->params, programs->name);
	envp = gen_envp();
	if (ft_strchr(programs->name, '/'))
	{
		if (isdir(programs->name))
			msg_dir(programs->name);
		else
		{
			execve(programs->name, argv, envp);
			msg_error_on_exec(programs->name);
		}
		exit_code = 126;
	}
	else
		exit_code = exec_from_path(programs->name, argv, envp);
	return (clear_memory(fstp, (char **)argv, &envp), destroy_hashtbl(),
		exit(exit_code));
}

static int	setup_to_exec(struct s_program *programs, struct s_exec *executor)
{
	if (programs->infile)
		executor->fdin = treat_infile(programs->infile, programs->h_pipe[0]);
	if (executor->fdin == -1)
		perror("minishell: infile");
	if (executor->fdin != -1)
	{
		dup2(executor->fdin, STDIN_FILENO);
		close(executor->fdin);
	}
	if (programs->next == NULL && programs->outfile)
		executor->fdout = treat_outfile(programs->outfile);
	else if (programs->next == NULL)
		executor->fdout = dup(executor->tmpout);
	else
	{
		if (pipe(executor->_pipe) == -1)
			return (perror("minishell: pipe"), 1);
		executor->fdin = executor->_pipe[0];
		executor->fdout = executor->_pipe[1];
		if (programs->outfile)
		{
			close(executor->fdout);
			executor->fdout = treat_outfile(programs->outfile);
		}
	}
	if (executor->fdout == -1)
		return (perror("minishell: fdout"), 1);
	return (dup2(executor->fdout, STDOUT_FILENO), close(executor->fdout), 0);
}

int	executor(struct s_program *programs)
{
	struct s_exec		exec;

	setup_signal(SIGINT, handler_exec);
	exec.tmpin = dup(STDIN_FILENO);
	exec.tmpout = dup(STDOUT_FILENO);
	if (NOT programs->infile)
		exec.fdin = dup(exec.tmpin);
	exec.fstprg = programs;
	while (programs)
	{
		if (setup_to_exec(programs, &exec))
		{
			programs = programs->next;
			continue ;
		}
		if (programs->name && is_builtin(programs))
			programs->exit_code = exec_builtin(programs, &exec);
		else if (programs->name)
		{
			programs->pid = fork();
			if (programs->pid == 0)
				exec_child(programs, &exec.fstprg, &exec);
		}
		programs = programs->next;
	}
	reset_stdin_stdout(exec.tmpin, exec.tmpout);
	return (wait_all(exec.fstprg),
		insert_ext_code(last_program(exec.fstprg)->exit_code), 0);
}
