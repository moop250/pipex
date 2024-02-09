/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:20:09 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/09 15:57:28 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_error(char *in)
{
	if (access(".swap", F_OK) == 0)
		unlink(".swap");
	perror(in);
	razegarbage();
	exit(EXIT_FAILURE);
}

void	px_free(char **in)
{
	int	i;

	i = -1;
	while (in[++i])
		gfree(in[i]);
	gfree(in);
}

void	px_excec(const char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = px_cmdwrk(cmd);
	if (!s_cmd)
		exit(EXIT_FAILURE);
	path = px_getpath(s_cmd[0], envp);
	if (execve(path, &s_cmd[0], envp) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s_cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		px_free(s_cmd);
		exit(127);
	}
}

char	*envpwrk(char *in, char **envp)
{
	int		i;
	int		a;
	char	*str;

	i = 0;
	while (envp[i])
	{
		a = 0;
		while (envp[i][a] && envp[i][a] != '=')
			a++;
		str = ft_substr(envp[i], 0, a);
		if (ft_strncmp(str, in, ft_strlen(in)) == 0)
		{
			gfree(str);
			return (envp[i] + a + 1);
		}
		gfree(str);
		i++;
	}
	return (NULL);
}

char	*px_getpath(char *cmd, char **envp)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	s_cmd = ft_split(cmd, ' ');
	allpath = ft_split(envpwrk("PATH", envp), ':');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		gfree(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			px_free(s_cmd);
			return (exec);
		}
		gfree(exec);
	}
	px_free(allpath);
	px_free(s_cmd);
	return (cmd);
}
