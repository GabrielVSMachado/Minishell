/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:27:51 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 01:50:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h"
#include "hashtable.h"
#include "error.h"
#include "linked_list.h"
#include <stdlib.h>

extern struct s_hashtbl	g_envs;

static int	print_envs(void)
{
	unsigned int	bucket;
	struct s_keyval	*tmp;

	bucket = 0;
	while (bucket < TBLSIZE)
	{
		tmp = g_envs.hashtbl[bucket];
		while (tmp)
		{
			if (*tmp->key == '?' && tmp->next == NULL)
				break ;
			else if (*tmp->key == '?')
				continue ;
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(tmp->val, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
			tmp = tmp->next;
		}
		bucket += 1;
	}
	return (0);
}

static int	is_interpreted_symbol(int c)
{
	return (ft_isdigit(c) || c == '?' || c == '!' || c == '-');
}

static int	check_valid_key(const char *word)
{
	int	counter;

	if (is_interpreted_symbol(*word))
		return (*word);
	counter = 0;
	while (word[counter] && word[counter] != '='
		&& (ft_isalnum(word[counter]) || word[counter] == '_'))
		counter += 1;
	return ((word[counter] && word[counter] != '=') * (word[counter]));
}

static void	insert_key(char *param)
{
	char			*equal;
	char			*key;

	equal = ft_strchr(param, '=');
	if (NOT equal)
		return ;
	key = ft_substr(param, 0, equal - (char *)param);
	if (hashtbl_lookup(key))
	{
		insert_hashtbl(key, ft_strdup(equal + 1));
		free(key);
	}
	else
		insert_hashtbl(key, ft_strdup(equal + 1));
}

int	export(const t_list *params)
{
	char			invalid_key;

	if (NOT params)
		return (print_envs());
	while (params)
	{
		invalid_key = check_valid_key(params->content);
		if (invalid_key || *((char *)params->content) == '=')
		{
			raise_error_on_export(params->content);
			params = params->next;
			continue ;
		}
		insert_key(params->content);
		params = params->next;
	}
	return (0);
}
