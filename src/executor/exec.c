/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 00:20:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "signals.h"
#include "error.h"
#include "parsing.h"
#include "minishell.h"
#include "hashtable.h"
#include "executor/utils_exec.h"
#include <errno.h>

static int	not_builtin(struct s_program *programs, struct s_exec *exc)
{
	char				**envp;
	char *const			*argv;
	int					ext_code;

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
		ext_code = 126 + (errno == ENOENT);
	}
	else
		ext_code = exec_from_path(programs->name, argv, envp);
	clear_memory(&exc->fstprg, (char **)argv, &envp);
	return (ext_code);
}

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
	int					exit_code;

	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGINT, SIG_DFL);
	exit_code = 0;
	if (exec->fdin != -1)
		close(exec->fdin);
	exec->fdin = -1;
	setup_to_exec(programs, exec);
	clear_fds_on_child(exec->fstprg, exec);
	if (programs->name)
	{
		if (is_builtin(programs))
		{
			exit_code = exec_builtin_pipeline(programs, exec);
			clear_memory(&exec->fstprg, NULL, NULL);
		}
		else
			exit_code = not_builtin(programs, exec);
	}
	else
		clear_memory(&exec->fstprg, NULL, NULL);
	destroy_hashtbl();
	exit(exit_code);
}

static void	setup_parent(struct s_program *programs, struct s_exec *exc)
{
	if (programs->next != NULL)
	{
		if (pipe(exc->_pipe) == -1)
		{
			perror("minishell: pipe");
			__exit(&exc->fstprg, NULL);
		}
		exc->fdin = exc->_pipe[0];
		exc->fdout = exc->_pipe[1];
	}
	else
		exc->fdout = dup(exc->tmpout);
	dup2(exc->fdout, STDOUT_FILENO);
	close(exc->fdout);
	exc->fdout = -1;
	programs->pid = fork();
	if (programs->pid == 0)
		exec_child(programs, exc);
}

void	exec_pipeline(struct s_program *programs)
{
	struct s_exec	exc;

	exc.tmpin = dup(STDIN_FILENO);
	exc.tmpout = dup(STDOUT_FILENO);
	exc.fdin = dup(STDIN_FILENO);
	setup_signal(SIGINT, handler_exec);
	exc.fstprg = programs;
	while (programs)
	{
		dup2(exc.fdin, STDIN_FILENO);
		close(exc.fdin);
		exc.fdin = -1;
		setup_parent(programs, &exc);
		programs = programs->next;
	}
	reset_stdin_stdout(exc.tmpin, exc.tmpout);
	wait_all(exc.fstprg);
	insert_ext_code(last_program(exc.fstprg)->exit_code);
}
