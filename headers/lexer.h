/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 21:29:32 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/01/03 21:29:32 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <linked_list.h>
# include <stddef.h>

enum	e_tokens
{
	INFILE,
	OUTFILE,
	WORD
};

int	token_infile(const char *line, size_t start, t_list **head);
int	token_word(const char *line, size_t start, t_list **head);
#endif
