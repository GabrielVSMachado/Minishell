/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/27 13:22:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include "executor.h"
#include "executor/utils_exec.h"
#include "ft_string.h"
#include "hashtable.h"
#include "libft.h"
#include "parsing.h"
#include "tokenizer.h"
#include "signals.h"
#include "expand/envs.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>

int	main(void)
{
	char				*line;
	struct s_tokens		*tokens;
	struct s_program	*programs;

	init_hashtbl();
	init_envs();
	while (TRUE)
	{
		setup_signal(SIGQUIT, SIG_IGN);
		setup_signal(SIGINT, handler_parent);
		line = readline("gvitor-s/f-tadeu@42sp[ minishell ]$ ");
		if (NOT line)
			return (0);
		tokens = tokenizer(line);
		free(line);
		programs = parsing(tokens);
		clear_tokens(&tokens);
		if (exec_heredocs(programs) != -1)
			executor(programs);
		destroy_programs(&programs);
	}
	return (0);
}
