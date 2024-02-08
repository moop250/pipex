/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:21 by hlibine           #+#    #+#             */
/*   Updated: 2024/02/08 15:01:24 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include "libft/srcs/libft.h"
# include <errno.h>
# include <stdio.h>

typedef struct s_key
{
	int		ac;
	char	**av;
	char	**env;
	int		in;
	int		out;
	int		cmdcount;
	char	***cmds;
}	t_key;

void	px_error(char *in);
void	px_free(char **in);
char	*px_getpath(char *cmd, char **envp);
char	**px_cmdwrk(const char *cmd);
void	px_excec(const char *cmd, char **envp);

#endif