/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:00:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/16 18:58:47 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/pipex.h"

/*
	with heredoc there is 4 argc params so i do -5 to compenasate
	for the fact that arrays start at 0
	same logic applies if there is no heredoc
*/

void	px_outfile(t_key *key, int argc, char **argv)
{
	if (key->heredoc)
	{
		key->cmdcount = argc - 5;
		key->out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else
	{
		key->out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		key->cmdcount = argc - 4;
	}
	if (key->out < 0)
		px_error("outfile");
}

void	errcmd(t_key *key, int pos)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(key->cmds[pos][0], 2);
	ft_putendl_fd(": command not found", 2);
	razegarbage();
	exit(127);
}

void	px_duppage(t_key *key, int pos, int *pipe0, int *pipe1)
{
	if (pos == 0)
	{
		dup2(key->in, STDIN_FILENO);
		close(key->in);
	}
	else
		dup2(pipe1[0], STDIN_FILENO);
	close(pipe1[0]);
	if (pos == key->cmdcount)
	{
		dup2(key->out, STDOUT_FILENO);
		close(key->out);
	}
	else
		dup2(pipe0[1], STDOUT_FILENO);
	close(pipe0[1]);
}

void	px_child(t_key *key, int pos, int *pipe0, int *pipe1)
{
	char	*path;

	path = px_getpath(key->cmds[pos][0], key->env);
	px_duppage(key, pos, pipe0, pipe1);
	if(execve(path, key->cmds[pos], key->env) == -1)
		errcmd(key, pos);
	exit(127);
}

void	px_waitchild(pid_t *pid, t_key *key)
{
	int	i;
	int	status;

	i = -1;
	while (++i < key->cmdcount)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	razegarbage();
	exit(status);
}
