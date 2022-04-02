/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:39:03 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/01 23:00:50 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "hashtable.h"
#include "minishell.h"
#include "tokenizer.h"
#include <asm-generic/ioctls.h>
#include <signal.h>
#include "signals.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

static void	handler_append_command_child(int sig, void *w_pipe)
{
	static int	*_;

	if (sig == SIGINT)
	{
		close(_[1]);
		_ = NULL;
		exit(130);
	}
	else
		_ = (int *)w_pipe;
}

static void	clean(int w_pipe, char **line, int EXCODE)
{
	free(*line);
	close(w_pipe);
	exit(EXCODE);
}

static void	exec_fork(int _pipe[2])
{
	struct s_tokens	*tokens;
	char			*line;
	void			*handler;

	handler_append_command_child(-1, _pipe);
	handler = &handler_append_command_child;
	setup_signal(SIGINT, (__sighandler_t)handler);
	setup_signal(SIGQUIT, SIG_IGN);
	destroy_hashtbl();
	while (close(_pipe[0]), 1)
	{
		line = readline("> ");
		if (line == NULL)
			return (close(_pipe[1]), exit(3));
		if (*line == '\0')
			continue ;
		tokens = tokenizer(line);
		if (NOT tokens)
			clean(_pipe[1], &line, EXIT_FAILURE);
		if (ft_putstr_fd(line, _pipe[1]), last_token(tokens)->token != T_PIPE)
			return (clear_tokens(&tokens), clean(_pipe[1], &line,
					EXIT_SUCCESS));
		clear_tokens(&tokens);
		free(line);
	}
}

static int	get_new_value_from_pipe(char **line, int r_pipe)
{
	int		len;

	if (ioctl(r_pipe, FIONREAD, &len))
	{
		perror("minishell");
		return (1);
	}
	*line = malloc(sizeof(char) * len + 1);
	if (read(r_pipe, *line, len) == -1)
	{
		free(*line);
		perror("minishell");
		return (1);
	}
	(*line)[len] = '\0';
	return (0);
}

int	append_command(char **line)
{
	int				ext_code;
	pid_t			pid;
	int				_pipe[2];

	setup_signal(SIGINT, handler_append_command);
	if (pipe(_pipe))
		return (perror("minishell"), 1);
	ft_putstr_fd(*line, _pipe[1]);
	free(*line);
	*line = NULL;
	pid = fork();
	if (pid == 0)
		exec_fork(_pipe);
	close(_pipe[1]);
	waitpid(pid, &ext_code, 0);
	ext_code = WEXITSTATUS(ext_code);
	if (ext_code == 0)
		get_new_value_from_pipe(line, _pipe[0]);
	close(_pipe[0]);
	if (ext_code == 3)
		__exit(NULL);
	return (ext_code);
}
