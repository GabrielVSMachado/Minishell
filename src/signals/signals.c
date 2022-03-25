/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/24 21:32:09 by gvitor-s         ###   ########.fr       */
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

void	handler_parent(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	insert_hashtbl("?", ft_itoa(sig + 128));
}

void	setup_signals(__sighandler_t h_quit, __sighandler_t h_int,
		struct sigaction *s_sigaction)
{
	ft_bzero(s_sigaction, sizeof(struct sigaction));
	s_sigaction->sa_handler = h_quit;
	sigaction(SIGQUIT, s_sigaction, NULL);
	s_sigaction->sa_handler = h_int;
	sigaction(SIGINT, s_sigaction, NULL);
}
