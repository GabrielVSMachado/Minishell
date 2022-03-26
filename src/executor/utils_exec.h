/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:08:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/26 14:43:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_EXEC_H
# define UTILS_EXEC_H

# include "libft.h"
# include "parsing.h"

struct s_exec
{
	int	fdin;
	int	fdout;
	int	tmpin;
	int	tmpout;
	int	_pipe[2];
};

int			exec_heredocs(struct s_program *programs);
int			wait_all(struct s_program *program);
void		garbage_collector(int init_fd);
char *const	*gen_argv(t_list *params, char *name);
char		**gen_envp(void);
void		delete_envp(char **envp);
char		*check_path(char const *program_name);
#endif
