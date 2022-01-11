/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:05:26 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/01/10 11:05:26 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(malloc(sizeof(char) * PATH_MAX), PATH_MAX);
	return (cwd);
}

int	pwd(void)
{
	char	*cwd;

	cwd = get_cwd();
	if (cwd == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		free(cwd);
		return (ERROR);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (SUCCESS);
}
