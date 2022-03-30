/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:23:04 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/29 20:49:37 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void	msg_dir(char *program_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(program_name, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
}

int	isdir(char *program_name)
{
	DIR	*dir;

	dir = opendir(program_name);
	if (NOT dir)
		return (0);
	closedir(dir);
	return (1);
}
