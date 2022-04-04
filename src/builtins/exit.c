/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 19:47:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 01:39:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
#include "ft_stdio.h"
#include "hashtable.h"
#include "linked_list.h"
#include "parsing.h"
#include <stdio.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

static int	is_numeric_arg(char *arg)
{
	while (arg && *arg)
	{
		if (NOT ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static int	check_ext_code(t_list *params)
{
	if (is_numeric_arg(params->content))
	{
		if (params->next)
		{
			ft_putendl_fd("minishell: exit: too many args", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else
			return (ft_atoi(params->content));
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(params->content, STDERR_FILENO);
		ft_putendl_fd(": numeric argument requeried", STDERR_FILENO);
		return (2);
	}
}

void	__exit(struct s_program **program, t_list *params)
{
	int	ext;

	ext = EXIT_SUCCESS;
	destroy_hashtbl();
	clear_history();
	if (NOT program || (*program)->builtin_code == EXIT)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (params)
		ext = check_ext_code(params);
	if (program)
		destroy_programs(program);
	exit(ext);
}
