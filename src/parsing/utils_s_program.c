/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_s_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:04:46 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/26 22:24:42 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "executor/utils_exec.h"
#include <stdlib.h>
#include <unistd.h>

struct s_program	*new_program(char *name)
{
	struct s_program	*new_p;

	new_p = malloc(sizeof(struct s_program));
	if (NOT new_p)
		return (NULL);
	new_p->name = name;
	new_p->pid = 0;
	new_p->h_pipe[0] = -1;
	new_p->h_pipe[1] = -1;
	new_p->infile = NULL;
	new_p->params = NULL;
	new_p->outfile = NULL;
	new_p->next = NULL;
	return (new_p);
}

struct	s_program	*last_program(struct s_program *head)
{
	struct s_program	*last;

	last = head;
	while (head)
	{
		last = head;
		head = head->next;
	}
	return (last);
}

void	add_program(struct s_program **head, struct s_program *new)
{
	if (*head)
		last_program(*head)->next = new;
	else
		*head = new;
}

static void	clear_struct_io(void *content)
{
	struct s_io	*tmp;

	tmp = (struct s_io *)content;
	free(tmp->file);
	tmp->type = 0;
	free(content);
	content = NULL;
}

void	destroy_programs(struct s_program **head)
{
	struct s_program	*tmp;

	clear_fds_on_programs(*head);
	while (*head)
	{
		tmp = (*head)->next;
		ft_lstclear(&(*head)->infile, clear_struct_io);
		ft_lstclear(&(*head)->outfile, clear_struct_io);
		ft_lstclear(&(*head)->params, free);
		free((*head)->name);
		free(*head);
		*head = NULL;
		*head = tmp;
	}
	head = NULL;
}
