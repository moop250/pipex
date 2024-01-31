/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 23:52:21 by hlibine           #+#    #+#             */
/*   Updated: 2024/01/31 11:19:11 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include <fcntl.h>
# include <unistd.h>
# include "libft/srcs/libft.h"
# include <errno.h>
# include <stdio.h>

void	px_error(char *in);
void	px_free(char **in);
char	*px_getpath(char *cmd, char **envp);
void	bonus_px_error(char *in);
char	*bonus_envpwrk(char *in, char **envp);
char	*bonus_px_getpath(char *cmd, char **envp);

#endif