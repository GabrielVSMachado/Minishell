/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 12:34:27 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/28 15:27:02 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "hashtable.h"
#include "linked_list.h"
#include "libft.h"
#include "minishell.h"
#include <linux/limits.h>
#include <stdio.h>
#include <unistd.h>

static int	cd_to_home(void)
{
	struct s_keyval	*home;
	t_list			home_env;

	home = hashtbl_lookup("HOME");
	if (NOT home)
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	else
	{
		home_env.content = home->val;
		home_env.next = NULL;
		(void)cd(&home_env);
	}
	return (home == NULL);
}

int	cd(t_list *param)
{
	if (NOT param)
		return (cd_to_home());
	else if (param->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (chdir(param->content))
	{
		perror("minishell: cd");
		return (1);
	}
	if (NOT hashtbl_lookup("PWD"))
		insert_hashtbl(ft_strdup("PWD"), getcwd(NULL, PATH_MAX));
	else
		insert_hashtbl("PWD", getcwd(NULL, PATH_MAX));
	return (0);
}
