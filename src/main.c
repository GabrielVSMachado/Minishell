/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 01:58:33 by gvitor-s         ###   ########.fr       */
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

static void	exec_commands(struct s_program **programs)
{
	struct s_exec	_;

	_.fstprg = *programs;
	_.tmpin = -1;
	_.tmpout = -1;
	if (exec_heredocs(*programs) == -1)
		return ;
	if (*programs && (*programs)->next)
		exec_pipeline(*programs);
	else if ((*programs)->name && is_builtin(*programs))
		insert_ext_code(exec_builtin(*programs, &_));
	else
		exec_pipeline(*programs);
}

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
	while (TRUE)
	{
		setup_signal(SIGINT, handler_parent);
		setup_signal(SIGQUIT, SIG_IGN);
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
		clear_tokens(&tokens);
		exec_commands(&programs);
		destroy_programs(&programs);
	}
}
