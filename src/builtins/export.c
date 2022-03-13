/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:27:51 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/13 16:24:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "hashtable.h"
#include "error.h"

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

int	export(const char *word)
{
	char	*equal;
	char	invalid_c;

	if (NOT word)
		return (print_envs());
	invalid_c = check_valid_key(word);
	if (invalid_c)
		return (raise_error_on_export(invalid_c));
	equal = ft_strchr(word, '=');
	if (NOT equal)
		return (0);
	insert_hashtbl(ft_substr(word, 0, equal - word), ft_strdup(equal + 1));
	return (0);
}
