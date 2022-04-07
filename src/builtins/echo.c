/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:35:20 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 00:33:21 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_str.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "linked_list.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*join_params(struct s_list *words)
{
	char	*joined_str;
	char	*tmp;

	if (NOT words)
		return (NULL);
	else if (words->next)
	{
		joined_str = ft_strdup(words->content);
		words = words->next;
		while (words)
		{
			tmp = ft_strjoin(joined_str, " ");
			free(joined_str);
			joined_str = ft_strjoin(tmp, words->content);
			free(tmp);
			words = words->next;
		}
	}
	else
		joined_str = ft_strdup(words->content);
	return (joined_str);
}

int	echo(struct s_list *params)
{
	char	*to_print;

	if (NOT params)
		ft_putendl_fd("", STDOUT_FILENO);
	else
	{
		if (ft_strcmp(params->content, "-n"))
		{
			to_print = join_params(params);
			ft_putendl_fd(to_print, STDOUT_FILENO);
		}
		else
		{
			while (NOT ft_strcmp(params->content, "-n"))
				params = params->next;
			to_print = join_params(params);
			ft_putstr_fd(to_print, STDOUT_FILENO);
		}
		free(to_print);
	}
	return (0);
}
