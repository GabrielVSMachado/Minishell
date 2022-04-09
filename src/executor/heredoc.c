/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:19:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/09 16:13:56 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "expand_str.h"
#include "parsing.h"
#include "signals.h"
#include "executor/utils_exec.h"

static void	heredoc_eof_abort_msg(char *delimiter)
{
	ft_putstr_fd(
		"minishell: warning: here-document delimited by end-of-file (wanted ",
		STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd(")", STDERR_FILENO);
}

static int	heredoc(struct s_io *infile, int w_pipe)
{
	char	*line;

	expand_quotes(&infile->file);
	line = readline("> ");
	while (line && ft_strcmp(line, infile->file))
	{
		(void)ft_putendl_fd(line, w_pipe);
		free(line);
		line = readline("> ");
	}
	if (line == NULL)
		heredoc_eof_abort_msg(infile->file);
	free(line);
	return (0);
}

static int	exec_child_heredoc(struct s_program *programs,
		struct s_program **tmp_programs, struct s_io *content)
{
	pid_t			pid;
	int				exit_status;
	void			*handler;

	exit_status = 0;
	if (programs->h_pipe[0] != -1)
		close(programs->h_pipe[0]);
	pipe(programs->h_pipe);
	pid = fork();
	if (pid == 0)
	{
		clear_history();
		handler_heredoc(0, tmp_programs);
		handler = &handler_heredoc;
		setup_signal(SIGINT, (__sighandler_t)handler);
		setup_signal(SIGQUIT, SIG_IGN);
		heredoc(content, programs->h_pipe[1]);
		clear_fds_on_programs(*tmp_programs);
		destroy_programs(tmp_programs);
		destroy_hashtbl();
		exit(0);
	}
	close(programs->h_pipe[1]);
	wait(&exit_status);
	return (WEXITSTATUS(exit_status));
}

int	exec_heredocs(struct s_program *programs)
{
	t_list				*infile;
	struct s_io			*content;
	struct s_program	*tmp_programs;

	tmp_programs = programs;
	setup_signal(SIGINT, handler_exec);
	while (programs)
	{
		infile = programs->r_io;
		while (infile)
		{
			content = infile->content;
			if (content->type == APPINFILE)
			{
				if (exec_child_heredoc(programs, &tmp_programs, content) != 0)
					return (-1);
			}
			infile = infile->next;
		}
		programs = programs->next;
	}
	return (0);
}
