/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 04:13:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "executor/utils_exec.h"
#include "hashtable.h"
#include "libft.h"
#include "parsing.h"
#include "tokenizer.h"
#include "signals.h"
#include "expand/envs.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "minishell.h"

static int	check_append_commands(char **line)
{
	int				last_is_pipe;
	struct s_tokens	*tokens;

	tokens = tokenizer(*line);
	if (NOT tokens)
		return (1);
	last_is_pipe = (last_token(tokens)->token == T_PIPE);
	clear_tokens(&tokens);
	if (last_is_pipe)
		return (append_command(line));
	return (0);
}

int	main(void)
{
	char				*line;
	struct s_tokens		*tokens;
	struct s_program	*programs;

	init_hashtbl();
	while (setup_signal(SIGQUIT, SIG_IGN), TRUE)
	{
		setup_signal(SIGINT, handler_parent);
		line = readline("gvitor-s/f-tadeu@42sp[ minishell ]$ ");
		if (NOT line)
			__exit(NULL, NULL);
		if (check_append_commands(&line))
		{
			free(line);
			continue ;
		}
		tokens = tokenizer(line);
		add_history(line);
		free(line);
		programs = parsing(tokens);
		if (clear_tokens(&tokens), programs && exec_heredocs(programs) != -1)
			executor(programs);
		destroy_programs(&programs);
	}
	return (0);
}
