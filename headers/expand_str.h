/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:19:37 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 00:25:03 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_STR_H
# define EXPAND_STR_H

# include "tokenizer.h"
# include "parsing.h"

void	expand_quotes(char **command);
void	expand_env_variables(char **word);
void	expand_all(struct s_program *programs);
#endif
