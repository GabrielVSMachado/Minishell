/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:43:08 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/23 12:56:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "tokenizer.h"

void	reset_stdin_stdout(int tmpin, int tmpout);
int		exit_errno(int tmpin, int tmpout);
int		raise_error_on_export(int invalid_c);
int		raise_tokenizer_err(char const *msg, struct s_tokens **info);
int		raise_env_error(void);
#endif
