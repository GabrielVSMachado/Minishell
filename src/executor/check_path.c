/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:52:28 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/01 17:20:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "hashtable.h"
#include "parsing.h"
#include "tokenizer.h"
#include <stdlib.h>
#include <unistd.h>

void	print_msg_command_not_found(char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putendl_fd(" command not found", STDERR_FILENO);
}

char	*check_path(char const *program_name)
{
	char			*program_path;
	char			**all_paths;
	int				position;
	char			*tmp;
	struct s_keyval	*path_env;

	path_env = hashtbl_lookup("PATH");
	if (NOT path_env || NOT program_name || NOT (*program_name))
		return (NULL);
	all_paths = ft_split(path_env->val, ':');
	position = -1;
	while (all_paths[++position])
	{
		tmp = ft_strjoin(all_paths[position], "/");
		program_path = ft_strjoin(tmp, program_name);
		free(tmp);
		if (access(program_path, F_OK) == 0)
			break ;
		free(program_path);
		program_path = NULL;
	}
	position = -1;
	while (all_paths[++position])
		free(all_paths[position]);
	return (free(all_paths), program_path);
}
