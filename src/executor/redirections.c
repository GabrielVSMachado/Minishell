/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:43:13 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 02:40:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/utils_exec.h"
#include "ft_stdio.h"
#include "linked_list.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

static int	set_fd(int *fd, struct s_io *io, int (*f)(struct s_io *))
{
	if (*fd != -1)
		close(*fd);
	*fd = f(io);
	if (*fd == -1)
		return (1);
	return (0);
}

static int	open_infiles(struct s_io *infile)
{
	int	fdin;

	fdin = open(infile->file, O_RDONLY | O_CLOEXEC);
	if (fdin == -1)
		perror("minishell: infile");
	return (fdin);
}

static int	open_outfile(struct s_io *outfile)
{
	int	fdout;

	fdout = open(outfile->file, O_WRONLY
			| (O_APPEND * (outfile->type == APPOUTFILE))
			| (O_TRUNC * (outfile->type != APPOUTFILE))
			| O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fdout == -1)
		perror("minishell: outfile");
	return (fdout);
}

int	exc_redirections(struct s_list *files, int *hr_pipe,
		struct s_exec *exc)
{
	struct s_io		*io;

	while (files)
	{
		io = files->content;
		if (io->type == INFILE)
		{
			if (*hr_pipe != -1)
			{
				close(*hr_pipe);
				*hr_pipe = -1;
			}
			if (set_fd(&exc->fdin, io, open_infiles))
				return (1);
		}
		else if (io->type == APPINFILE)
			exc->fdin = *hr_pipe;
		else
			if (set_fd(&exc->fdout, io, open_outfile))
				return (1);
		files = files->next;
	}
	return (0);
}
