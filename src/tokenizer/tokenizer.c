/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:28:40 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/02/09 22:28:40 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include "error.h"
#include <stdio.h>

static int	is_special(char	const c)
{
	return (ft_strchr("|&()><", c) != NULL);
}

static void	which_other_tokens(struct s_tokens **head, char const *line,
		unsigned int *cursor)
{
	add_back_token(head, new_token(
			NULL,
			T_PIPE * (line[*cursor] == '|' && line[*cursor + 1] != '|')
			+ T_OR * (line[*cursor] == '|' && line[*cursor + 1] == '|')
			+ T_CPARENTHESIS * (line[*cursor] == ')')
			+ T_OPARENTHESIS * (line[*cursor] == '(')
			+ T_AND * (line[*cursor] == '&' && line[*cursor + 1] == '&')
			+ T_RAOUTPUT * (line[*cursor] == '>' && line[*cursor + 1] == '>')
			+ T_RINPUT * (line[*cursor] == '<')
			+ T_ROUTPUT * (line[*cursor] == '>')
			+ T_HEREDOC * (line[*cursor] == '<' && line[*cursor] == '<')
			));
}

static int	treat_words(struct s_tokens **head, char const *line,
		unsigned int *cursor)
{
	unsigned int	counter;
	unsigned char	c;
	char			*next_quotes;

	counter = *cursor + 1;
	while (line[counter] != '\0' && !is_special(line[counter]))
	{
		c = ('\'' * (line[counter] == '\''))
			+ ('\"' * (line[counter] == '\"'));
		if (c != 0)
		{	
			next_quotes = ft_strchr(line + counter + 1, c);
			if (next_quotes == NULL)
				return (raise_tokenizer_err(
						"bad format string: unclosed quotes", head));
			counter += (next_quotes - (line + counter));
		}
		counter += 1;
	}
	add_back_token(head,
		new_token(ft_substr(line, *cursor, counter - *cursor), T_WORD));
	(*cursor) += counter;
	return (0);
}

struct s_tokens	*tokenizer(char const *line)
{
	struct s_tokens	*head;
	unsigned int	cursor;

	head = NULL;
	cursor = 0;
	while (line[cursor] != '\0')
	{
		if (is_special(line[cursor]))
			which_other_tokens(&head, line, &cursor);
		else
		{
			if (treat_words(&head, line, &cursor) == -1)
				return (NULL);
			continue ;
		}
		cursor += 1;
	}
	return (head);
}
