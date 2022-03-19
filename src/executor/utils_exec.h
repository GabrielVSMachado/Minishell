/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:08:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/19 14:07:27 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_EXEC_H
# define UTILS_EXEC_H

# include "libft.h"
# include "parsing.h"

char *const	*gen_argv(t_list *params, char *name);
char		*check_path(char const *program_name);
int			heredoc(struct s_io *infile);
#endif
