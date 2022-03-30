/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:32:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/30 00:45:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	msg_error_on_exec(char *prog_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(prog_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	clear_fds_on_child(struct s_program *fstp, struct s_exec *exec)
{
	clear_fds_on_programs(fstp);
	close(exec->tmpin);
	close(exec->tmpout);
	close(exec->fdin);
}

void	clear_memory(struct s_program **fstp, char **argv, char ***envp)
{
	free(argv);
	delete_envp(*envp);
	destroy_programs(fstp);
}

int	exec_from_path(char *program_name, char *const *argv, char **envp)
{
	char	*path;

	path = check_path(program_name);
	if (path)
	{
		execve(path, argv, envp);
		msg_error_on_exec(program_name);
	}
	else
		print_msg_command_not_found(program_name);
	return (free(path), 126 + path == NULL);
}
