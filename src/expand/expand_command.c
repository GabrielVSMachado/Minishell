/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:59:48 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/22 20:23:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_str.h"
#include "parsing.h"

void	expand_program(struct s_program *programs)
{
	struct s_list		*tmp;
	struct s_io			*content;

	expand_command(&programs->name);
	tmp = programs->infile;
	while (tmp)
	{
		content = (struct s_io *)tmp->content;
		expand_command(&content->file);
		tmp = tmp->next;
	}
	tmp = programs->outfile;
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

void	expand_command(char **word)
{
	expand_env_variables(word);
	expand_quotes(word);
}
