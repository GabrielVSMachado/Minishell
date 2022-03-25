/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:59:09 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/24 21:19:06 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	handler_parent(int sig);
void	setup_signals(__sighandler_t h_quit, __sighandler_t h_int,
			struct sigaction *s_sigaction);
#endif
