/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/01 23:34:05 by gvitor-s         ###   ########.fr       */
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
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "minishell.h"

int	main(void)
{
	char				*line;
	struct s_tokens		*tokens;
	struct s_program	*programs;
	int					last_is_pipe;

	init_hashtbl();
	init_envs();
	while (setup_signal(SIGQUIT, SIG_IGN), TRUE)
	{
		setup_signal(SIGINT, handler_parent);
		line = readline("gvitor-s/f-tadeu@42sp[ minishell ]$ ");
		if (NOT line)
			__exit(NULL);
		tokens = tokenizer(line);
		if (NOT tokens)
		{
			free(line);
			continue ;
		}
		last_is_pipe = (last_token(tokens)->token == T_PIPE);
		if (clear_tokens(&tokens), last_is_pipe && append_command(&line))
			continue ;
		tokens = tokenizer(line);
		free(line);
		programs = parsing(tokens);
		if (clear_tokens(&tokens), programs && exec_heredocs(programs) != -1)
			executor(programs);
		destroy_programs(&programs);
	}
	return (0);
}
