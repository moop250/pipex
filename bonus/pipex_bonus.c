/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 16:47:58 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"
#include "get_next_line/get_next_line.h"

void	heredoc(t_key *key)
{
	char	*line;
	char	*out;
	int		flag;

	out = ft_strdup("");
	if (!out)
		px_error("malloc");
	flag = 0;
	while (flag != 1)
	{
		line = get_next_line(0);
		if (ft_strncmp(key->av[2], line, ft_strlen(line) - 1) != 0)
			out = ft_strjoin(out, line);
		else
			flag = 1;
		if (!out)
			px_error("malloc");
		free(line);
	}
	key->in = open(".swap", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (key->in < 0)
		px_error("Error: Failed to create swap file");
	ft_putstr_fd(out, key->in);
	free(out);
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
	out = galloc(cmds * sizeof(char**));
	if (!out)
		px_error("malloc");
	while (i < cmds)
	{
		out[i] = px_cmdwrk(argv[a]);
		if (!out[i])
			px_3dfree(out);
		++i;
		++a;
	}
	return (out);
}

t_key	*keywrk(int argc, char **argv, char **envp)
{
	t_key	*key;

	key = galloc(sizeof(t_key));
	if (!key)
		px_error("malloc");
	key->ac = argc;
	key->av = argv;
	if (!ft_strncmp(key->av[1], "heredoc", ft_strlen(key->av[1])))
		key->in = open(key->av[1], O_RDONLY, 0644);
	else
		heredoc(key);
	if (!key->in)
		px_error("infile")
	key->env = envp;
	px_outfile(key, argc, argv);
	key->cmds = cmdparser(key->cmdcount, argv, envp);
	if (!key->cmds)
		px_error("malloc");
	return (key);
}

void	pipewrk(t_key *key)
{
	t_list	*pid;
	int		*pipes[2];
	int		i;

	i = -1;
	while (++i < key->cmdcount)
	{
		
		ft_lstadd_front(pid, ft_lstnew(fork())); 
		if (!*pid->content)
			px_error("galloc")
		else if (*pid->content == -1)
			px_error("fork");
		else
			PARENT (NOT NULL)
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_key	*key;

	if (argc < 5 || (argc < 6 &&
		!ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1]))))
		px_error("not enough arguments");
	key = keywrk(argc, argv, envp);
	pipewrk(key);
	if (access(".swap", F_OK) == 0)
		unlink(".swap");
}

/* int	main(void)
{
	return (0);
} */
