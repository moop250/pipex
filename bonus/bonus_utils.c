/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:00:04 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/12 16:32:42 by hlibine          ###   ########.fr       */
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

void	px_child_start()
{
	if ()
}

void	px_middle_child()
{
	
}

void	px_child(t_key *key, int childnum, int *pipe0, int *pipe1)
{
	if (childnum == 0)
		dup2(key->in, STDIN_FILENO);
	else
		dup2(pipe1[0], STDIN_FILENO);
	if (childnum == key->cmdcount)
		dup2(key->out, STDOUT_FILENO);
	else
		dup2(pipe0[1]);
	execv(px_getpath(key->cmds[childnum][0]), &key->cmds[childnum], key->env)
}

void	px_waitchild(t_list pid)
{
	
}