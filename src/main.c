/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 20:41:00 by gvitor-s          #+#    #+#             */
/*   Updated: 2021/12/23 20:41:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

int	main(void)
{
	char	*line;

	while (TRUE)
	{
		line = readline("gvitor-s/f-tadeu@42sp[ minishell ]$");
		free(line);
	}
	return (EXIT_SUCCESS);
}
