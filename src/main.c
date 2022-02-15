/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/23 20:41:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(void)
{
	char			*line;
	struct s_tokens	*head;

	head = NULL;
	while (TRUE)
	{
		line = readline("gvitor-s/f-tadeu@42sp[ minishell ]$ ");
		if (line == NULL)
		{
			clear_tokens(&head);
			break ;
		}
		head = tokenizer(line);
		printf("%s\n", head->value);
		if (!head)
		{
			free(line);
			continue ;
		}
		free(line);
		clear_tokens(&head);
	}
	return (EXIT_SUCCESS);
}
