/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:17:26 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/11 19:56:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envs.h"
#include "libft.h"
#include "hashtable.h"

extern struct s_hashtbl	g_envs;

static char	*make_new_string(char	*tmp)
{
	char	*dollar;
	t_list	*to_join;
	char	*new_str;

	to_join = NULL;
	dollar = ft_strchr(tmp, '$');
	while (dollar)
	{
		ft_lstadd_back(&to_join, ft_lstnew(
				ft_substr(tmp, 0, dollar - tmp)));
		ft_lstadd_back(&to_join, ft_lstnew(treat_envs(dollar)));
		tmp += ((dollar - tmp + 1) + len_env_name(dollar));
		dollar = ft_strchr(tmp, '$');
	}
	ft_lstadd_back(&to_join, ft_lstnew(ft_strdup(tmp)));
	new_str = join_command(to_join);
	ft_lstclear(&to_join, free);
	return (new_str);
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
	result_str = ft_substr(holder, 0, len_str);
	ft_lstadd_back(llist, ft_lstnew(result_str));
	return (len_str);
}

static int	add_string_delimited_by_c(char *str, struct s_list **llist,
		char c)
{
	char			*string_to_add;
	unsigned int	len_string;

	len_string = ft_strchr(str + 1, c) - str;
	string_to_add = ft_substr(str, 0, len_string + 1);
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
	if (NOT ft_strchr(tmp, '$'))
		return ;
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
