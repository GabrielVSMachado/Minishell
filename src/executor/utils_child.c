/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 21:32:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/30 00:04:10 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
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

void	clear_memory(struct s_program **fstp, char **argv, char ***envp,
		char *path)
{
	free(argv);
	free(path);
	delete_envp(*envp);
	destroy_programs(fstp);
}
