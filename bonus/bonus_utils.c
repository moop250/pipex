/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:00:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/08 17:10:08 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"

void	px_3dfree(void ***array)
{
	int		i;
	int		a;

	i = 0;
	while (array[i])
	{
		a = 0;
		while (array[i][a])
		{
			free(array[i][a]);
			++a;
		}
		free(array[i]);
		++i;
	}
	free(array);
}