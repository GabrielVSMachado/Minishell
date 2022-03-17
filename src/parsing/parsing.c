/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:55:01 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/17 14:57:02 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parsing.h"
#include "libft.h"

static void	add_outfile(struct s_program **program, struct s_tokens **head)
{
	struct s_program	*last;

	if (NOT (*program))
		add_program(program, new_program(NULL));
	last = last_program(*program);
	ft_lstadd_back(&last->outfile, ft_lstnew(
			new_io(ft_strdup((*head)->next->value),
				OUTFILE * ((*head)->token == T_ROUTPUT)
				+ APPOUTFILE * ((*head)->token == T_RAOUTPUT)
				)
			));
	*head = (*head)->next->next;
}

static void	parsing_program(struct s_program **program, struct s_tokens **head)
{
	struct s_program	*last;

	last = last_program(*program);
	if (last && NOT last->name)
		last->name = ft_strdup((*head)->value);
	else
	{
		add_program(program, new_program(ft_strdup((*head)->value)));
		last = last_program(*program);
	}
	*head = (*head)->next;
	while (*head && (*head)->token == T_WORD)
	{
		ft_lstadd_back(&last->params, ft_lstnew(ft_strdup((*head)->value)));
		*head = (*head)->next;
	}
}

static void	add_infile(struct s_program **program, struct s_tokens **head)
{
	struct s_program	*last;

	if (NOT (*program))
		add_program(program, new_program(NULL));
	last = last_program(*program);
	ft_lstadd_back(&last->infile, ft_lstnew(
			new_io(ft_strdup((*head)->next->value),
				INFILE * ((*head)->token == T_RINPUT)
				+ APPINFILE * ((*head)->token == T_HEREDOC)
				)
			));
	*head = (*head)->next->next;
}

struct s_program	*parsing(struct s_tokens *head)
{
	struct s_program	*programs;

	programs = NULL;
	while (head)
	{
		if (head->token == T_WORD)
			parsing_program(&programs, &head);
		else if (head->token == T_RINPUT || head->token == T_HEREDOC)
			add_infile(&programs, &head);
		else if (head->token == T_ROUTPUT || head->token == T_RAOUTPUT)
			add_outfile(&programs, &head);
		else if (head->token == T_PIPE)
		{
			add_program(&programs, new_program(NULL));
			head = head->next;
		}
	}
	return (programs);
}
