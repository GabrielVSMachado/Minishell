/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:27:54 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 00:15:52 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
#include "libft.h"
#include "parsing.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void	wait_all(struct s_program *program)
{
	struct s_program	*llst;
	int					issignaled;

	llst = program;
	while (program)
	{
		waitpid(program->pid, &program->exit_code, 0);
		program = program->next;
	}
	while (llst)
	{
		issignaled = WIFSIGNALED(llst->exit_code);
		llst->exit_code = (issignaled * (WTERMSIG(llst->exit_code) + 128)
				+ (NOT issignaled) * WEXITSTATUS(llst->exit_code));
		llst = llst->next;
	}
}
