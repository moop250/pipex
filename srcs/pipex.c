/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:06 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/05 16:21:13 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_error(char *in)
{
	perror(in);
	exit(EXIT_FAILURE);
}

void	excec(const char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = px_cmdwrk(cmd);
	if (!s_cmd)
		exit(EXIT_FAILURE);
	path = px_getpath(s_cmd[0], envp);
	if (execve(path, &s_cmd[0], envp) == -1)
	{
		ft_putstr_fd("pipex error: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		px_free(s_cmd);
		exit(EXIT_FAILURE);
	}
}

void	child_ps(int *e_fd, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0644);
	if (fd < 0)
		px_error("Error: Failed to open input file");
	dup2(fd, STDIN_FILENO);
	close(e_fd[0]);
	dup2(e_fd[1], STDOUT_FILENO);
	close(e_fd[1]);
	excec(argv[2], envp);
}

void	parent_ps(int *e_fd, char **argv, char **envp)
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		px_error("Error: Failed to open output file");
	dup2(fd, STDOUT_FILENO);
	close(e_fd[1]);
	dup2(e_fd[0], STDIN_FILENO);
	close(e_fd[0]);
	excec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid[2];

	if (argc != 5)
		px_error("not enough / too many arguments");
	if (pipe(fd) == -1)
		px_error("Error: Failed to open the pipe");
	pid[0] = fork();
	if (pid[0] == -1)
		px_error("Error: Failed to open fork");
	if (!pid[0])
		child_ps(fd, argv, envp);
	else
	{
		pid[1] = fork();
		if (pid[1] == -1)
			px_error("Error: Failed to open fork");
		if (pid[1])
			parent_ps(fd, argv, envp, pid);
		else
			waitpid(pid)
	}
}
