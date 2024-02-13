/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/13 15:23:43 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//e_fd = external file descriptor
void	child_ps(int *e_fd, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
		px_error("pipex: input");
	dup2(fd, STDIN_FILENO);
	close(e_fd[0]);
	dup2(e_fd[1], STDOUT_FILENO);
	close(e_fd[1]);
	px_excec(argv[2], envp);
}

//e_fd = external file descriptor
void	child2_ps(int *e_fd, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		px_error("pipex: output");
	dup2(fd, STDOUT_FILENO);
	close(e_fd[1]);
	dup2(e_fd[0], STDIN_FILENO);
	close(e_fd[0]);
	px_excec(argv[3], envp);
}

void	parent_ps(int *fd, char **argv, char **envp, int *pid)
{
	int	status;
	int	i;

	i = -1;
	pid[1] = fork();
	if (pid[1] == -1)
		px_error("pipex: Failed to open fork");
	else if (!pid[1])
		child2_ps(fd, argv, envp);
	close(fd[1]);
	while (++i < 2)
		waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 0;
	close(fd[0]);
	exit(status);
}

//fd is the pipe (i know poor naming convention but i wat tired)
int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (argc != 5)
		px_error("not enough / too many arguments");
	if (pipe(fd) == -1)
		px_error("pipex: Failed to open the pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		px_error("pipex: Failed to open fork");
	else if (!pid[0])
		child_ps(fd, argv, envp);
	parent_ps(fd, argv, envp, pid);
	razegarbage();
}
