/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:59:09 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/26 19:04:14 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	handler_heredoc(int sig);
void	handler_exec(int sig);
void	handler_parent(int sig);
void	setup_signals(__sighandler_t h_quit, __sighandler_t h_int);
#endif
