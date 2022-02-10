/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:03:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/02/08 22:03:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>

struct s_tokens
{
	unsigned int	token;
	char			*value;
	struct s_tokens	*next;
};

enum	e_tokens
{
	T_WORD,
};

void			add_back_token(struct s_tokens **head, struct s_tokens *new);
struct s_tokens	*new_token(char *content, unsigned int token);
struct s_tokens	*last_token(struct s_tokens *head);
#endif
