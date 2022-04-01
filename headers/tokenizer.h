/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:03:53 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/31 22:34:13 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define NOT	!
# define AND	&&
# define OR		||

struct s_tokens
{
	unsigned int	token;
	char			*value;
	struct s_tokens	*next;
};

enum	e_tokens
{
	T_WORD,
	T_RINPUT,
	T_ROUTPUT,
	T_RAOUTPUT,
	T_HEREDOC,
	T_PIPE,
};

int				append_command(char **line);
struct s_tokens	*find_token(struct s_tokens *head, unsigned int token);
void			add_back_token(struct s_tokens **head, struct s_tokens *new);
void			clear_tokens(struct s_tokens **head);
struct s_tokens	*new_token(char *content, unsigned int token);
struct s_tokens	*last_token(struct s_tokens *head);
struct s_tokens	*tokenizer(char const *line);
struct s_tokens	*check_tokens(struct s_tokens **head);
#endif
