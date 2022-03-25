/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/24 21:19:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "hashtable.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

void	handler_parent(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	insert_hashtbl("?", ft_itoa(130));
}

void	setup_signals(__sighandler_t h_quit, __sighandler_t h_int,
		struct sigaction *s_sigaction)
{
	s_sigaction->sa_handler = h_quit;
	sigaction(SIGQUIT, s_sigaction, NULL);
	s_sigaction->sa_handler = h_int;
	sigaction(SIGINT, s_sigaction, NULL);
}
