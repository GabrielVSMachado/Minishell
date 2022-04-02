/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 02:59:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include "executor/utils_exec.h"
#include "parsing.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

void	handler_heredoc(int sig, void *programs)
{
	static struct s_program	**_;

	if (sig == SIGINT)
	{
		destroy_programs(_);
		_ = NULL;
		destroy_hashtbl();
		rl_on_new_line();
		rl_replace_line("", 0);
		exit(128 + sig);
	}
	else
		_ = (struct s_program **)programs;
}

void	handler_exec(int sig)
{
	insert_ext_code(128 + sig);
	write(STDOUT_FILENO, "\n", 1);
}

void	handler_parent(int sig)
{
	insert_ext_code(128 + sig);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

void	setup_signal(int sig, __sighandler_t h)
{
	struct sigaction	s_sigaction;

	s_sigaction = (struct sigaction){};
	s_sigaction.sa_flags = SA_RESTART;
	s_sigaction.sa_handler = h;
	sigaction(sig, &s_sigaction, NULL);
}
