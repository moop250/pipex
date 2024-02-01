/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmdprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:33:55 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/01 16:50:16 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **px_realloc(char **in)
{
	char	**out;
	size_t	arraylen;
	int		i;

	i = 0;
	arraylen = 0;
	while (in[arraylen])
		++arraylen;
	out = malloc((arraylen * sizeof(char *) + 1));
	if (!out)
		px_error("Error: Malloc failure");
	while (in[i])
	{
		out[i] = in[i];
		++i;
	}
	if(in)
		free(in);
	return(out);
}

/* 
i[0] == position in cmd
i[1] == position in out array
i[2] == flag
pos[0] == start
pos[1] == end
*/
char	**cmdwrk(char *cmd)
{
	char	**out;
	int		i[3];
	char	tmp;
	int		pos[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (cmd[i[0]])
	{
		while (cmd[i[0]] == ' ' && cmd[i[0]])
			++i[0];
		pos[0] = i[0];
		if (cmd[i[0]] == 34 || cmd[i[0]] == 39)
		{
			i[2] == 1;
			tmp = cmd[i[0]];
		}
		if (i[2] = 0)
			while (cmd[i[0]] && cmd[i[0]] != ' ' && cmd[i[0]] != 34 && cmd[i[0]] != 39)
				++i[0];
		else
			while (cmd[i[0]] && cmd[i[0]] != tmp)
				++i[0];
		i[2] = 0;
		pos[1] = i[0];
		out = px_realloc(out);
		out[i[1]] = ft_substr(cmd, pos[0], pos[1] - pos[0])
		++i[1];
	}
	return (out);
}