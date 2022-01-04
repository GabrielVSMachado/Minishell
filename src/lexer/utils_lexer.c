/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:32:47 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/01/03 18:32:47 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_special_char(const char c)
{
	return (c == '>' || c == '<' || c == '|'
		|| c == '$' || c == '\'' || c == '\"');
}

int	token_word(const char *line, size_t start, t_list **head)
{
	int	len_word;

	len_word = 0;
	while (line[start + len_word] != 0
		&& !is_special_char(line[start + len_word])
		&& line[start + len_word] != ' ')
		len_word += 1;
	ft_lstadd_back(head, ft_lstnew(ft_substr(line, start, len_word)));
	return (len_word);
}

int	token_infile(const char *line, size_t start, t_list **head)
{
	int	len_infile;

	len_infile = 0;
	while (line[start] == ' ')
		start += 1;
	while (ft_isalpha(line[start + len_infile]))
		len_infile += 1;
	ft_lstadd_back(head, ft_lstnew(ft_substr(line, start, len_infile)));
	return (len_infile);
}
