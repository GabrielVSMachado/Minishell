/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:50:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/05 15:50:25 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_command(struct s_list *to_join)
{
	char	*result;
	char	*tmp;

	result = to_join->content;
	to_join->content = NULL;
	to_join = to_join->next;
	while (to_join)
	{
		tmp = ft_strjoin(result, to_join->content);
		free(result);
		result = tmp;
		if (NOT result)
			return (free(result), NULL);
		to_join = to_join->next;
	}
	return (result);
}

static size_t	distance_to_next_quote(char *tmp)
{
	size_t	len;

	len = 0;
	while (*tmp AND (*tmp != '\'' AND (*tmp != '"')))
	{
		tmp += 1;
		len += 1;
	}
	return (len);
}

static size_t	word_before_quotes(struct s_list **to_join, char *tmp)
{
	size_t	len;

	len = distance_to_next_quote(tmp);
	ft_lstadd_back(to_join, ft_lstnew(ft_memcpy(malloc(len + 1), tmp, len)));
	((char *)(ft_lstlast(*to_join)->content))[len] = 0;
	return (len);
}

static size_t	extract_word_inside_quotes(struct s_list **to_join, char *tmp,
		char c)
{
	size_t	len;

	tmp += 1;
	len = ft_strchr(tmp, c) - tmp;
	ft_lstadd_back(to_join,
		ft_lstnew(ft_memcpy(malloc(len + 1), tmp, len)));
	((char *)(ft_lstlast(*to_join)->content))[len] = 0;
	return (len + 2);
}

void	expand_quotes(char **command)
{
	char			*tmp;
	struct s_list	*to_join;
	char			c;

	tmp = *command;
	if (NOT (ft_strchr(tmp, '\'') OR ft_strchr(tmp, '"')))
		return ;
	to_join = NULL;
	while (*tmp)
	{
		c = '\'' * (*tmp == '\'') + '"' * (*tmp == '"');
		if (c)
			tmp += extract_word_inside_quotes(&to_join, tmp, c);
		else
			tmp += word_before_quotes(&to_join, tmp);
	}
	free(*command);
	*command = join_command(to_join);
	ft_lstclear(&to_join, free);
}
