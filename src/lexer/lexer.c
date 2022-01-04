/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 14:40:44 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/31 14:40:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsing(const char *line)
{
	size_t	index;
	size_t	movs;
	t_list	*head[4];

	ft_bzero(head, sizeof(t_list) * 4);
	index = 0;
	while (line[index] != '\0')
	{
		movs = 1;
		if (ft_isalpha(line[index]))
			movs = token_word(line, index, &head[WORD]);
		else if (line[index] == '<')
			movs = token_infile(line, index + 1, &head[INFILE]);
		index += movs;
	}
}
