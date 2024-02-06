/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_cmdprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:33:55 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/06 11:24:39 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	findend(int i, const char *cmd)
{
	int	a;

	a = 0;
	if (cmd[i] == 34 || cmd[i] == 39)
	{
		a = cmd[i];
		++i;
	}
	if (a == 0)
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != 34 && cmd[i] != 39)
			++i;
	else
	{
		while (cmd[i] && cmd[i] != a)
			++i;
		++i;
	}
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

/*
i[0] == position in cmd
i[1] == position in out array
pos[0] == start
pos[1] == end
*/
char	**px_cmdwrk(const char *cmd)
{
	char	**out;
	int		i[2];
	int		pos[2];
	int		cs;

	i[0] = 0;
	i[1] = 0;
	out = NULL;
	cs = sizeof(char *);
	while (cmd[i[0]])
	{
		while (cmd[i[0]] == ' ' && cmd[i[0]])
			++i[0];
		pos[0] = i[0];
		i[0] = findend(i[0], cmd);
		pos[1] = i[0];
		out = ft_realloc(out, i[1] * cs, (i[1] + 2) * cs);
		out[i[1]] = ft_substr(cmd, pos[0], pos[1] - pos[0]);
		out[i[1] + 1] = NULL;
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
		printf("%s\n", out[i]);
		free(out[i]);
		i++;
	}
	free(out);
	close(fd);
	return 0;
} */
