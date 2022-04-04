/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:08:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 02:29:17 by gvitor-s         ###   ########.fr       */
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
	struct s_program	*fstprg;
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

int			exc_redirections(struct s_list *files, int *hr_pipe,
				struct s_exec *exc);
void		msg_error_on_exec(char *prog_name);
void		clear_memory(struct s_program **fstp, char **argv, char ***envp);
void		clear_fds_on_child(struct s_program *fstp, struct s_exec *exec);
void		msg_dir(char *program_name);
int			isdir(char *program_name);
int			exec_builtin(struct s_program *current_prog, struct s_exec *exc);
int			is_builtin(struct s_program *program);
void		print_msg_command_not_found(char *name);
int			exec_heredocs(struct s_program *programs);
void		wait_all(struct s_program *program);
void		clear_fds_on_programs(struct s_program *programs);
char *const	*gen_argv(t_list *params, char *name);
char		**gen_envp(void);
void		delete_envp(char **envp);
char		*check_path(char const *program_name);
int			exec_from_path(char *program_name, char *const *argv, char **envp);
#endif
