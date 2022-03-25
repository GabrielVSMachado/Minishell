/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/25 15:41:34 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

void	handler_exec(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handler_parent(int sig)
{
	insert_hashtbl("?", ft_itoa(sig + 128));
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(__sighandler_t h_quit, __sighandler_t h_int)
{
	struct sigaction	s_sigaction;

	s_sigaction = (struct sigaction){};
	s_sigaction.sa_handler = h_quit;
	sigaction(SIGQUIT, &s_sigaction, NULL);
	s_sigaction.sa_handler = h_int;
	sigaction(SIGINT, &s_sigaction, NULL);
}
