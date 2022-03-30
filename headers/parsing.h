/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:57:57 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/30 12:41:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "tokenizer.h"
# include <sys/types.h>

struct	s_program
{
	char				*name;
	pid_t				pid;
	int					h_pipe[2];
	int					builtin_code;
	int					exit_code;
	t_list				*params;
	t_list				*infile;
	t_list				*outfile;
	struct s_program	*next;
};

struct s_io
{
	unsigned int	type;
	char			*file;
};

enum e_parsing
{
	APPINFILE,
	INFILE,
	OUTFILE,
	APPOUTFILE
};

void				add_program(struct s_program **head,
						struct s_program *new);
struct s_program	*new_program(char *name);
struct s_program	*last_program(struct s_program *head);
void				destroy_programs(struct s_program **head);
struct s_program	*parsing(struct s_tokens *head);
struct s_io			*new_io(char *content, unsigned int type);
#endif
