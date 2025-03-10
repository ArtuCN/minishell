/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:12 by adonato           #+#    #+#             */
/*   Updated: 2024/07/09 15:48:31 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fork_p(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	return (pid);
}

void	execve_p(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
		return ;
}

void	pipe_p(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		return ;
}

void	wait_p(int *status)
{
	if (wait(status) == -1)
		return ;
}

int	access_p(char *file, int mode)
{
	int	ret;

	ret = access(file, mode);
	if (ret == -1 && errno != ENOENT)
		return (0);
	return (ret);
}
