/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:13:13 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 00:20:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
#include "expand_str.h"
#include "ft_string.h"
#include "hashtable.h"
#include "minishell.h"
#include "parsing.h"
#include "error.h"
#include <unistd.h>

int	is_builtin(struct s_program *program)
{
	if (NOT ft_strcmp("echo", program->name))
		program->builtin_code = ECHO;
	else if (NOT ft_strcmp("cd", program->name))
		program->builtin_code = CD;
	else if (NOT ft_strcmp("export", program->name))
		program->builtin_code = EXPORT;
	else if (NOT ft_strcmp("env", program->name))
		program->builtin_code = ENV;
	else if (NOT ft_strcmp("unset", program->name))
		program->builtin_code = UNSET;
	else if (NOT ft_strcmp("exit", program->name))
		program->builtin_code = EXIT;
	else if (NOT ft_strcmp("pwd", program->name))
		program->builtin_code = PWD;
	return (program->builtin_code != -1);
}

int	exec_builtin_pipeline(struct s_program *current_prog, struct s_exec *exc)
{
	int	exit_status;

	exit_status = 0;
	if (current_prog->builtin_code == ECHO)
		exit_status = echo(current_prog->params);
	else if (current_prog->builtin_code == CD)
		exit_status = cd(current_prog->params);
	else if (current_prog->builtin_code == EXPORT)
		exit_status = export(current_prog->params);
	else if (current_prog->builtin_code == UNSET)
		unset(current_prog->params);
	else if (current_prog->builtin_code == ENV)
		env();
	else if (current_prog->builtin_code == EXIT)
		__exit(&(exc->fstprg), current_prog->params);
	else if (current_prog->builtin_code == PWD)
		exit_status = pwd();
	return (exit_status);
}

static int	setup_to_exec_builtin(struct s_program *program, struct s_exec *exc)
{
	if (exc_redirections(program->r_io, &program->h_pipe[0], exc))
	{
		if (exc->fdin != -1)
			close(exc->fdin);
		if (exc->fdout != -1)
			close(exc->fdout);
		clear_fds_on_child(exc->fstprg, exc);
		return (1);
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

int	exec_builtin_parent(struct s_program *current_prog, struct s_exec *exc)
{
	int	exit_status;

	if (setup_to_exec_builtin(current_prog, exc))
		return (reset_stdin_stdout(exc->tmpin, exc->tmpout), 1);
	exit_status = 0;
	if (current_prog->builtin_code == ECHO)
		exit_status = echo(current_prog->params);
	else if (current_prog->builtin_code == CD)
		exit_status = cd(current_prog->params);
	else if (current_prog->builtin_code == EXPORT)
		exit_status = export(current_prog->params);
	else if (current_prog->builtin_code == UNSET)
		unset(current_prog->params);
	else if (current_prog->builtin_code == ENV)
		env();
	else if (current_prog->builtin_code == EXIT)
	{
		reset_stdin_stdout(exc->tmpin, exc->tmpout);
		__exit(&(exc->fstprg), current_prog->params);
	}
	else if (current_prog->builtin_code == PWD)
		exit_status = pwd();
	return (reset_stdin_stdout(exc->tmpin, exc->tmpout), exit_status);
}
