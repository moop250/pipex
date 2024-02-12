/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:00:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/12 17:23:39 by hlibine          ###   ########.fr       */
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

void	px_child(t_key *key, int pos, int *pipe0, int *pipe1)
{
	if (pos == 0)
	{
		dup2(key->in, STDIN_FILENO);
		close(key->in);
	}
	else
	{
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[0]);
	}
	if (pos == key->cmdcount)
	{
		dup2(key->out, STDOUT_FILENO);
		close(key->out);
	}
	else
	{
		dup2(pipe0[1]);
		close(pipe0[1]);
	}
	if (execve(px_getpath(key->cmds[pos][0]), &key->cmds[pos], key->env) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(key->cmds[pos][0], 2);
		ft_putendl_fd(": command not found", 2);
		razegarbage();
		exit(127);
	}
}

void	px_waitchild(t_list pid)
{
	
}