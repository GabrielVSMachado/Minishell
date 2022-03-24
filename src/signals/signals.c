/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:54:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/24 13:56:54 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>

void	setup_signals(void)
{
	struct sigaction	s_sigaction;

	s_sigaction = (struct sigaction){};
	s_sigaction.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_sigaction, NULL);
}
