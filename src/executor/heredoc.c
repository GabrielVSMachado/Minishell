/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:19:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/25 14:35:32 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"
#include "parsing.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "expand_str.h"

static void	heredoc_eof_abort_msg(char *delimiter)
{
	ft_putstr_fd(
		"minishell: warning: here-document delimited by end-of-file (wanted ",
		STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd(")", STDERR_FILENO);
}

int	heredoc(struct s_io *infile)
{
	int		_pipe[2];
	char	*line;
	int		save;

	expand_quotes(&infile->file);
	save = errno;
	(void)pipe(_pipe);
	line = readline(">");
	while (line && ft_strcmp(line, infile->file))
	{
		(void)ft_putendl_fd(line, _pipe[1]);
		free(line);
		line = readline(">");
	}
	if (line == NULL)
		heredoc_eof_abort_msg(infile->file);
	free(line);
	line = NULL;
	(void)close(_pipe[1]);
	errno = save;
	return (_pipe[0]);
}
