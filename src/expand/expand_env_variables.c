/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:17:26 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/11 00:26:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"
#include "libft.h"
#include "hashtable.h"

extern struct s_hashtbl	g_envs;

static char	*make_new_string(char	*tmp)
{
	struct s_list			*to_join;
	struct s_list			*expanded_strings;
	struct s_str_map_helper	helper;
	char					*result;

	to_join = NULL;
	expanded_strings = NULL;
	helper.dollar_c = ft_strchr(tmp, '$');
	while (helper.dollar_c)
	{
		helper.len_prev = helper.dollar_c - tmp;
		helper.prev_str = ft_memcpy(malloc(helper.len_prev + 1), tmp, helper.len_prev);
		helper.prev_str[helper.len_prev] = 0;
		ft_lstadd_back(&to_join, ft_lstnew(helper.prev_str));
		ft_lstadd_back(&to_join, ft_lstnew(treat_envs(helper.dollar_c)));
		tmp += (helper.len_prev + len_env_name(helper.dollar_c) + 1);
		helper.dollar_c = ft_strchr(tmp, '$');
		if (NOT helper.dollar_c)
			ft_lstadd_back(&to_join, ft_lstnew(ft_strdup(tmp)));
		ft_lstadd_back(&expanded_strings, ft_lstnew(join_command(to_join)));
		ft_lstclear(&to_join, free);
	}
	result = join_command(expanded_strings);
	ft_lstclear(&expanded_strings, free);
	return (result);
}

static void	*map_helper(void *content)
{
	char	*tmp;

	tmp = (char *)content;
	if (*tmp != '\'')
		return (make_new_string(tmp));
	return (ft_strdup((char *)content));
}

static int	add_string_without_quotes(char *tmp, struct s_list **llist)
{
	char			*holder;
	char			*result_str;
	unsigned int	len_str;

	holder = tmp;
	while (*tmp && *tmp != '\'' && *tmp != '"')
		tmp += 1;
	len_str = tmp - holder;
	result_str = ft_memcpy(malloc(len_str + 1), holder, len_str);
	result_str[len_str] = 0;
	ft_lstadd_back(llist, ft_lstnew(result_str));
	return (len_str);
}

static int	add_string_delimited_by_c(char *str, struct s_list **llist,
		char c)
{
	char			*string_to_add;
	unsigned int	len_string;

	len_string = ft_strchr(str + 1, c) - str;
	string_to_add = ft_memcpy(malloc(len_string + 2), str, len_string + 1);
	string_to_add[len_string + 1] = 0;
	ft_lstadd_back(llist, ft_lstnew(string_to_add));
	return (len_string + 1);
}

void	expand_env_variables(char **word)
{
	t_list	*to_join;
	t_list	*to_expand_env;
	char	*tmp;
	char	c;

	tmp = *word;
	to_join = NULL;
	to_expand_env = NULL;
	while (*tmp)
	{
		c = '\'' * (*tmp == '\'') + '"' * (*tmp == '"');
		if (c)
		{
			tmp += add_string_delimited_by_c(tmp, &to_expand_env, c);
			continue ;
		}
		tmp += add_string_without_quotes(tmp, &to_expand_env);
	}
	to_join = ft_lstmap(to_expand_env, map_helper, free);
	ft_lstclear(&to_expand_env, free);
	free(*word);
	*word = join_command(to_join);
	ft_lstclear(&to_join, free);
}
