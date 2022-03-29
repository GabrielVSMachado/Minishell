/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:08:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/28 21:00:09 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_EXEC_H
# define UTILS_EXEC_H

# include "libft.h"
# include "parsing.h"

struct s_exec
{
	int					fdin;
	int					fdout;
	int					tmpin;
	int					tmpout;
	int					_pipe[2];
	int					exit_status;
	struct s_program	*first_prog;
};

enum e_builtin
{
	ECHO = 1,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

int			exec_builtin(struct s_program *current_prog,
				struct s_program **first_prog);
int			is_builtin(struct s_program *program);
void		print_msg_command_not_found(char *name);
int			exec_heredocs(struct s_program *programs);
int			wait_all(struct s_program *program);
void		clear_fds_on_programs(struct s_program *programs);
char *const	*gen_argv(t_list *params, char *name);
char		**gen_envp(void);
void		delete_envp(char **envp);
char		*check_path(char const *program_name);
#endif
