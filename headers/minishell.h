/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:35 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/28 17:05:45 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "linked_list.h"
# include "parsing.h"

int		pwd(void);
int		cd(t_list *params);
void	env(void);
void	unset(const char *key);
int		export(t_list *params);
int		echo(struct s_list *params);
void	__exit(struct s_program *programs);
#endif
