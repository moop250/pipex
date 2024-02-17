/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/17 01:44:07 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"
#include "get_next_line/get_next_line.h"

void	heredoc(t_key *key)
{
	char	*line;
	char	*out;
	int		flag;
	char	*tmp;

	out = ft_strdup("");
	flag = 0;
	while (flag != 1)
	{
		line = get_next_line(0);
		if (ft_strncmp(key->av[2], line, ft_strlen(line) - 1) != 0)
		{
			tmp = ft_strjoin(out, line);
			gfree(out);
			out = tmp;
		}
		else
			flag = 1;
		gfree(line);
	}
	key->in = open(".swap", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (key->in < 0)
		px_error("Error: Failed to create swap file");
	ft_putstr_fd(out, key->in);
	gfree(out);
}

char	***cmdparser(int cmds, bool heredoc, char **argv)
{
	char	***out;
	int		i;
	int		a;

	i = 0;
	a = 2;
	if (heredoc)
		a = 3;
	out = galloc(cmds * sizeof(char **));
	while (i <=cmds)
	{
		out[i] = px_cmdwrk(argv[a]);
		++i;
		++a;
	}
	return (out);
}

t_key	*keywrk(int argc, char **argv, char **envp)
{
	t_key	*key;

	key = galloc(sizeof(t_key));
	key->ac = argc;
	key->av = argv;
	if (!ft_strncmp(key->av[1], "heredoc", ft_strlen(key->av[1])))
		key->heredoc = true;
	else
		key->heredoc = false;
	if (!key->heredoc)
		key->in = open(key->av[1], O_RDONLY, 0644);
	else
		heredoc(key);
	if (key->in < 0)
		px_error("infile");
	key->env = envp;
	px_outfile(key, argc, argv);
	key->cmds = cmdparser(key->cmdcount, key->heredoc, argv);
	return (key);
}

void	pipewrk(t_key *key)
{
	pid_t	*pid;
	int		*pipes[2];
	int		i;

	i = -1;
	pid = galloc(sizeof(pid_t) * (key->cmdcount + 1));
	while (++i <= key->cmdcount)
	{
		pipes[0] = galloc(sizeof(int) * 2);
		pipe(pipes[0]);
		pid[i] = fork();
		if (pid[i] == -1)
			px_error("fork");
		else if (pid[i] == 0)
			px_child(key, i, pipes[0], pipes[1]);
		close (pipes[0][1]);
		if (pipes[1])
			close (pipes[1][0]);
		pipes[1] = pipes[0];
	}
	px_waitchild(pid, key);
}

int	main(int argc, char **argv, char **envp)
{
	t_key	*key;

	if (argc < 5 || (argc < 6
			&& !ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1]))))
		px_error("not enough arguments");
	key = keywrk(argc, argv, envp);
	pipewrk(key);
	if (access(".swap", F_OK) == 0)
		unlink(".swap");
	razegarbage();
	return (1);
}

/* int	main(void)
{
	return (0);
} */
