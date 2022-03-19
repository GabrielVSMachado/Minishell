/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:19:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/19 16:29:28 by gvitor-s         ###   ########.fr       */
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

int	heredoc(struct s_io *infile)
{
	int		_pipe[2];
	char	*line;
	int		save;

	save = errno;
	(void)pipe(_pipe);
	line = readline(">");
	while (ft_strcmp(line, infile->file))
	{
		(void)ft_putendl_fd(line, _pipe[1]);
		free(line);
		line = readline(">");
	}
	free(line);
	line = NULL;
	(void)close(_pipe[1]);
	errno = save;
	return (_pipe[0]);
}
