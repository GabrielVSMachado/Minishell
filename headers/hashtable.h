/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:54:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/12 19:31:17 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define TBLSIZE 1237

struct s_keyval
{
	char			*key;
	char			*val;
	struct s_keyval	*next;
};

struct	s_hashtbl
{
	struct s_keyval	**hashtbl;
	unsigned int	size;
};

int					init_hashtbl(void);
struct s_keyval		*remove_key(const char *key);
struct s_keyval		*hashtbl_lookup(const char *key);
void				insert_hashtbl(const char *key, const char *value);
void				destroy_hashtbl(void);
#endif
