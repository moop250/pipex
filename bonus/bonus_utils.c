/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:00:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 16:34:55 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"

void	px_outfile(t_key *key, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1])))
	{
		key->cmdcount = argc - 4;
		key->out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		key->out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		key->cmdcount = argc - 3;
	}
	if (key->out < 0)
		px_error("outfile");
}