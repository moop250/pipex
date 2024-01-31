/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:20:09 by hlibine           #+#    #+#             */
/*   Updated: 2024/01/31 16:09:32 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_free(char **in)
{
	int	i;

	i = -1;
	while (in[++i])
		free(in[i]);
	free(in);
}

char **px_realloc(char **in)
{
	char	**out;
	size_t	arraylen;
	int		i;

	i = 0;
	arraylen = 0;
	while (in[arraylen])
		++arraylen;
	out = malloc((arraylen * sizeof(char *) + 1));
	if (!out)
		px_error("Error: Malloc failure");
	while (in[i])
	{
		out[i] = in[i];
		++i;
	}
	free(in);
	return(out);
}

// do a substring
char	**cmdwrk(char *cmd)
{
	char	**out;
	int		i;
	char	tmp;
	int		flag;

	i = 0;
	flag = 0;
	out = malloc(1 * sizeof(char *));
	if (!out)
		px_error("Error: Malloc failure");
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ' && cmd[i - 1] != ' ' && flag == 0)
			++i;
		if (cmd[i] == '"' || cmd[i] == 39)
		{
			if (flag == 0)
				tmp = cmd[i];
			else if (flag == 1 && cmd[i] == tmp)
				flag = 0;
		}
		
	}
	return (out);
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
			free(str);
			return (envp[i] + a + 1);
		}
		free(str);
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
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			px_free(s_cmd);
			return (exec);
		}
		free(exec);
	}
	px_free(allpath);
	px_free(s_cmd);
	return (cmd);
}
