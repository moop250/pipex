/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmdprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:33:55 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/07 13:52:32 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	findend(int i, const char *cmd, int flag)
{
	if (flag == 0)
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != 34 && cmd[i] != 39)
			++i;
	else
		while (cmd[i] && cmd[i] != flag)
			++i;
	return (i);
}

void	*ft_realloc(void *in, size_t oldsize, size_t newsize)
{
	void	*out;

	out = malloc(newsize);
	if (!out)
		return (NULL);
	if (!in)
		return (out);
	out = ft_memcpy(out, in, oldsize);
	free(in);
	return (out);
}

char	**outwrk(char **out, int *i, int *pos, const char *cmd)
{
	int	cs;

	cs = sizeof(char *);
	out = ft_realloc(out, i[1] * cs, (i[1] + 2) * cs);
	out[i[1]] = ft_substr(cmd, pos[0], pos[1] - pos[0]);
	out[i[1] + 1] = NULL;
	return (out);
}

/*
i[0] == position in cmd
i[1] == position in out array
pos[0] == start
pos[1] == end
*/
char	**px_cmdwrk(const char *cmd)
{
	char	**out;
	int		i[3];
	int		pos[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	out = NULL;
	while (cmd[i[0]])
	{
		while (cmd[i[0]] == ' ' && cmd[i[0]])
			++i[0];
		if (cmd[i[0]] == '\'' || cmd[i[0]] == '\"')
		{
			i[2] = cmd[i[0]];
			++i[0];
		}
		pos[0] = i[0];
		i[0] = findend(i[0], cmd, i[2]);
		pos[1] = i[0];
		if (i[2] != 0)
			++i[0];
		i[2] = 0;
		out = outwrk(out, i, pos, cmd);
		++i[1];
	}
	return (out);
}

/* int	main(int argc, char **argv)
{
	char **out;
	int	i;
	int	fd;

	fd = open("log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	i = 0;
	dup2(fd, 1);
	out = px_cmdwrk(argv[1]);
	while (out[i])
	{
		printf("line : %s\n", out[i]);
		free(out[i]);
		i++;
	}
	free(out);
	close(fd);
	return 0;
} */
