/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:27:54 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/24 21:17:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	wait_all(struct s_program *program)
{
	int	exit_status;

	exit_status = 0;
	while (program)
	{
		waitpid(program->pid, &exit_status, 0);
		program = program->next;
	}
	if (WIFSIGNALED(exit_status))
		return (WTERMSIG(exit_status) + 128);
	return (WEXITSTATUS(exit_status));
}
