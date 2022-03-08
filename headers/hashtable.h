/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:54:06 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/08 18:08:52 by gvitor-s         ###   ########.fr       */
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
	struct s_keyval	*hashtbl[TBLSIZE];
	unsigned int	size;
};

struct s_hashtbl	*hashtbl_init(void);
struct s_keyval		*hashtbl_lookup(const char *key);
void				insert_hashtbl(const char *key, const char *value);
#endif
