/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:43:13 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/04 01:28:16 by gvitor-s         ###   ########.fr       */
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
			if (exc->fdin != -1)
				close(exc->fdin);
			if (*hr_pipe != -1)
			{
				close(*hr_pipe);
				*hr_pipe = -1;
			}
			exc->fdin = open_infiles(io);
			if (exc->fdin == -1)
				return (1);
		}
		else if (io->type == APPINFILE)
			exc->fdin = *hr_pipe;
		else
		{
			if (exc->fdout != -1)
				close(exc->fdout);
			exc->fdout = open_outfile(io);
			if (exc->fdout == -1)
				return (1);
		}
		files = files->next;
	}
	return (0);
}
