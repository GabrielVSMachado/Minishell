/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:27:51 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/28 12:22:20 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashtable.h"
#include "error.h"
#include "linked_list.h"

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

int	export(const t_list *params)
{
	char	*equal;
	char	invalid_key;

	if (NOT params)
		return (print_envs());
	while (params)
	{
		invalid_key = check_valid_key(params->content);
		if (invalid_key)
		{
			raise_error_on_export(invalid_key);
			params = params->next;
			continue ;
		}
		equal = ft_strchr(params->content, '=');
		if (NOT equal)
		{
			params = params->next;
			continue ;
		}
		insert_hashtbl(ft_substr(params->content, 0,
				equal - (char *)params->content), ft_strdup(equal + 1));
		params = params->next;
	}
	return (0);
}
