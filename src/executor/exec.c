/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 01:54:00 by gvitor-s         ###   ########.fr       */
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
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "utils_exec.h"
#include "error.h"

static int	setup_to_exec(struct s_program *program, struct s_exec *exc)
{
	if (exc_redirections(program->r_io, &program->h_pipe[0], exc))
	{
		if (exc->fdin != -1)
			close(exc->fdin);
		if (exc->fdout != -1)
			close(exc->fdout);
		clear_fds_on_child(exc->fstprg, exc);
		destroy_hashtbl();
		destroy_programs(&exc->fstprg);
		exit(1);
	}
	if (exc->fdin != -1)
	{
		dup2(exc->fdin, STDIN_FILENO);
		close(exc->fdin);
		exc->fdin = -1;
	}
	if (exc->fdout != -1)
	{
		dup2(exc->fdout, STDOUT_FILENO);
		close(exc->fdout);
		exc->fdout = -1;
	}
	return (0);
}

static void	exec_child(struct s_program *programs, struct s_exec *exec)
{
	char				**envp;
	char *const			*argv;
	int					exit_code;

	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGINT, SIG_DFL);
	if (exec->fdin != -1)
		close(exec->fdin);
	exec->fdin = -1;
	setup_to_exec(programs, exec);
	clear_fds_on_child(exec->fstprg, exec);
	if (is_builtin(programs))
	{
		exit_code = exec_builtin(programs, exec);
		clear_memory(&exec->fstprg, NULL, NULL);
	}
	else
	{
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
		clear_memory(&exec->fstprg, (char **)argv, &envp);
	}
	destroy_hashtbl();
	exit(exit_code);
}

void	exec_pipeline(struct s_program *programs)
{
	struct s_exec	exc;

	exc.tmpin = dup(STDIN_FILENO);
	exc.tmpout = dup(STDOUT_FILENO);
	exc.fdin = dup(STDIN_FILENO);
	setup_signal(SIGINT, handler_exec);
	setup_signal(SIGQUIT, SIG_DFL);
	exc.fstprg = programs;
	while (programs)
	{
		dup2(exc.fdin, STDIN_FILENO);
		close(exc.fdin);
		exc.fdin = -1;
		if (programs->name)
		{
			if (programs->next != NULL)
			{
				if (pipe(exc._pipe) == -1)
				{
					perror("minishell: pipe");
					destroy_hashtbl();
					destroy_programs(&exc.fstprg);
					exit(errno);
				}
				exc.fdin = exc._pipe[0];
				exc.fdout = exc._pipe[1];
			}
			else
				exc.fdout = dup(exc.tmpout);
			dup2(exc.fdout, STDOUT_FILENO);
			close(exc.fdout);
			exc.fdout = -1;
			programs->pid = fork();
			if (programs->pid == 0)
				exec_child(programs, &exc);
		}
		programs = programs->next;
	}
	reset_stdin_stdout(exc.tmpin, exc.tmpout);
	wait_all(exc.fstprg);
	insert_ext_code(last_program(exc.fstprg)->exit_code);
}
