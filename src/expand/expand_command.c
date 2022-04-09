/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:59:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/09 16:05:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_str.h"
#include "parsing.h"

static void	expand_command(char **word)
{
	expand_env_variables(word);
	expand_quotes(word);
}

static void	expand_program(struct s_program *programs)
{
	struct s_list		*tmp;
	struct s_io			*content;

	if (programs->name)
		expand_command(&programs->name);
	tmp = programs->r_io;
	while (tmp)
	{
		content = (struct s_io *)tmp->content;
		expand_command(&content->file);
		tmp = tmp->next;
	}
	tmp = programs->params;
	while (tmp)
	{
		expand_command((char **)&tmp->content);
		tmp = tmp->next;
	}
}

void	expand_all(struct s_program *programs)
{
	while (programs)
	{
		expand_program(programs);
		programs = programs->next;
	}
}
