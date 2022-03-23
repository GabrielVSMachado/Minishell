/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:27:54 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/23 13:29:10 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <sys/wait.h>

int	wait_all(struct s_program *program)
{
	int	exit_status;

	exit_status = 0;
	while (program)
	{
		waitpid(program->pid, &exit_status, 0);
		program = program->next;
	}
	return (exit_status);
}
