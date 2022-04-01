/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 23:26:01 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/31 21:44:27 by gvitor-s         ###   ########.fr       */
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

static int	validate_parenthesis(struct s_tokens *head)
{
	int				counter;
	struct s_tokens	*tmp;

	tmp = find_token(head, T_OPARENTHESIS);
	tmp = (struct s_tokens *)(((unsigned long int)tmp) | ((tmp == NULL) * (
					(unsigned long int)find_token(head, T_CPARENTHESIS))));
	if (NOT tmp)
		return (1);
	counter = 0;
	while (tmp)
	{
		if (counter < 0 || (tmp->token == T_OPARENTHESIS
				AND tmp->next->token == T_CPARENTHESIS))
			return (0);
		counter += (
				tmp->token == T_OPARENTHESIS) - (tmp->token == T_CPARENTHESIS);
		tmp = tmp->next;
	}
	return (counter == 0);
}

struct s_tokens	*check_tokens(struct s_tokens **head)
{
	struct s_tokens	*tmp;

	tmp = *head;
	if (NOT validate_parenthesis(tmp))
		raise_tokenizer_err("Parenthesis error", head);
	if (tmp->token == T_PIPE AND tmp->next == NULL)
		raise_tokenizer_err("Invalid character near `|'", head);
	while (tmp)
	{
		if (is_redirection(tmp->token) AND NOT is_valid_word(tmp->next))
		{
			raise_tokenizer_err("Invalid character near redirection", head);
			break ;
		}
		else if (tmp->token == T_PIPE AND tmp->next
			AND (!(is_redirection(tmp->next->token) OR is_valid_word(tmp->next)
					OR tmp->next->token == T_OPARENTHESIS)
				OR tmp->next->token == T_PIPE))
		{
			raise_tokenizer_err("Invalid character near `|'", head);
			break ;
		}
		tmp = tmp->next;
	}
	return (*head);
}
