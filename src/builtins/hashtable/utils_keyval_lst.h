/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_keyval_lst.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:27:17 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/09 13:04:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_KEYVAL_LST_H
# define UTILS_KEYVAL_LST_H

struct s_keyval	*new_node_of_bucket(char *key, char *value);
struct s_keyval	*last_node_of_bucket(struct s_keyval *bucket);
void			keyval_add_back(struct s_keyval **bucket, struct s_keyval *new);
void			clear_bucket(struct s_keyval **bucket);
#endif
