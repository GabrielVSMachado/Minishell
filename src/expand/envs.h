/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:55:30 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/03/10 23:58:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVS_H
# define ENVS_H

# include "libft.h"

struct s_str_map_helper
{
	char			*dollar_c;
	char			*prev_str;
	char			*result;
	unsigned int	len_prev;
};

unsigned int	len_env_name(char *env_name);
char			*treat_envs(char *env_name);
char			*join_command(struct s_list *to_join);
int				init_envs(void);
#endif
