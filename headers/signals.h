/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:59:09 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/02 02:47:01 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	handler_exec(int sig);
void	handler_heredoc(int sig, void *programs);
void	handler_parent(int sig);
void	setup_signal(int sig, __sighandler_t h);
#endif
