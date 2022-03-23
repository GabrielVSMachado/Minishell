/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 11:44:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/22 19:37:45 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "libft.h"
#include "linked_list.h"
#include "parsing.h"
#include <stddef.h>
#include <stdlib.h>
#include "hashtable.h"
#include <errno.h>

extern struct s_hashtbl	g_envs;

char *const	*gen_argv(t_list *params, char *name)
{
	char *const	*argv;
	char		**tmp;
	size_t		lenlst;

	lenlst = ft_lstsize(params);
	argv = malloc(sizeof(char *) * (lenlst + 2));
	tmp = (char **)argv;
	*tmp = name;
	tmp += 1;
	while (lenlst--)
	{
		*tmp = params->content;
		params = params->next;
		tmp += 1;
	}
	*tmp = NULL;
	return (argv);
}

static char	*join_key_val(const char *key, const char *value)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strjoin(key, "=");
	joined = ft_strjoin(tmp, value);
	free(tmp);
	tmp = NULL;
	return (joined);
}

char	**gen_envp(void)
{
	char			**envp;
	struct s_keyval	*llst;
	unsigned int	bucket;
	unsigned int	counter;

	envp = malloc(sizeof(char *) * (g_envs.size + 1));
	bucket = 0;
	counter = 0;
	while (bucket < TBLSIZE)
	{
		llst = g_envs.hashtbl[bucket];
		while (llst)
		{
			envp[counter] = join_key_val(llst->key, llst->val);
			llst = llst->next;
			counter += 1;
		}
		bucket += 1;
	}
	envp[g_envs.size] = NULL;
	return (envp);
}

void	delete_envp(char **envp)
{
	unsigned int	tmp;

	tmp = 0;
	while (tmp < g_envs.size)
	{
		free(envp[tmp]);
		tmp += 1;
	}
	free(envp);
	envp = NULL;
}

void	garbage_collector(int init_fd)
{
	int	fd;
	int	saved;

	fd = init_fd;
	saved = errno;
	while (errno != EBADF)
		(void)close(fd++);
	errno = saved;
}
