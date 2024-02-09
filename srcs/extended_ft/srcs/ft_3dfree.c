/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3dfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:11:29 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:14:27 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

void	ft_3dfree(void ***array)
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
