/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 23:26:01 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/02/17 23:26:01 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "error.h"
#include <stdlib.h>

static int	is_redirection(unsigned int token)
{
	return (token == T_RINPUT || token == T_HEREDOC
		|| token == T_ROUTPUT || token == T_RAOUTPUT);
}

static int	is_valid_word(struct s_tokens *token)
{
	return (token->token == T_WORD && token->value != NULL);
}

struct s_tokens	*check_tokens(struct s_tokens **head)
{
	struct s_tokens	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (is_redirection(tmp->token) && NOT is_valid_word(tmp->next))
			raise_tokenizer_err("Invalid character after redirection", head);
		else if (tmp->token == T_OPARENTHESIS
			&& (tmp->next->token == T_CPARENTHESIS
				|| NOT find_token(tmp, T_CPARENTHESIS)))
			raise_tokenizer_err("Parenthesis not closed", head);
		else if (tmp->token == T_PIPE && NOT (
				is_redirection(tmp->next->token) || is_valid_word(tmp->next)
				|| tmp->next->token == T_OPARENTHESIS))
			raise_tokenizer_err("Invalid character after T_PIPE", head);
		tmp = tmp->next;
	}
	return (*head);
}
