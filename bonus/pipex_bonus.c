/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/08 16:00:51 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"
#include "get_next_line/get_next_line.h"

int	heredoc(char *limiter)
{
	char	*line;
	char	*out;
	int		flag;

	out = ft_strdup("");
	flag = 0;
	while (flag != 1)
	{
		line = get_next_line(0);
		if (ft_strncmp(limiter, line, ft_strlen(line) - 1) != 0)
			out = ft_strjoin(out, line);
		else
			flag = 1;
		free(line);
	}
	flag = open(".swap", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (flag < 0)
		px_error("Error: Failed to creat swap file");
	ft_putstr_fd(out, flag);
	free(out);
	return (flag);
}

void	pipewrk(t_key key)
{
	
}

char ***cmdparser(int cmds, char **argv, char **envp)
{
	char	***out;
	int		i;
	int		a;

	i = 0;
	a = 2;
	if (ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1])))
		a = 3;
	out = malloc(cmds * sizeof(char**));
	if (!out)
		return(NULL);
	while (i < cmds)
	{
		out[i] = px_cmdwrk(argv[a]);
		if (!out[i])
			//make freeing function
		++i;
		++a;
	}
	return (out);
}

t_key	keywrk(int argc, char **argv, char **envp)
{
	t_key	key;

	key = malloc(sizeof(t_key));
	key->ac = argc;
	key->av = argv;
	key->env = envp;
	key->in = argc[1];
	key->out = argc[argc - 1];
	if (ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1])))
		key->cmdcount = argc - 4;
	else
		key->cmdcount = argc - 3;
	key->cmds = cmdparser(key->cmdcount, argv, envp);
	if (!key->cmds)
		px_error("pipex_bonus: malloc");
	return (key);
}

int	main(int argc, char **argv, char **envp)
{
	t_key	key;

	if (argc < 5)
		px_error("pipex: not enough arguments");
	key = keywrk(argc, argv, envp);
	pipewrk(key);
}
