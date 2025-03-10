/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:40:51 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <sys/stat.h>
#include <dirent.h>

int	compare_folder(t_shell *shell, struct dirent *curr, char *str)
{
	int	fd;

	fd = open(curr->d_name, __O_DIRECTORY);
	if (fd == -1 && str[0] != '.')
		return (ft_error(shell, NOT_FOLDER, str), 1);
	else if (fd != -1)
	{
		close(fd);
		return (ft_error(shell, FOLDER, str), 1);
	}
	close(fd);
	return (0);
}

int	not_folder(char *str)
{
	int		fd;
	char	*temp;

	if (str[0] != '/')
		temp = ft_strtrim(str, "/");
	else
		temp = ft_strdup(str);
	fd = open(temp, O_RDONLY);
	free(temp);
	if (fd != -1)
		return (1);
	close(fd);
	return (0);
}

int	is_folder(t_shell *shell, char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir)
	{
		closedir(dir);
		ft_error(shell, FOLDER, str);
		return (1);
	}
	else if (str[0] != '.' && not_folder(str))
		return (ft_error(shell, NOT_FOLDER, str), 1);
	if (access(str, F_OK) == -1)
		return (ft_error(shell, NO_FILE, str), 1);
	return (0);
}

int	not_binary(t_shell *shell, char *str)
{
	char			buffer[4];
	struct stat		path_stat;
	ssize_t			bytes_read;
	int				fd;

	if (stat(str, &path_stat) != 0)
		return (1);
	if (!S_ISREG(path_stat.st_mode) || !(path_stat.st_mode & S_IXUSR))
		return (1);
	fd = open(str, O_RDONLY);
	if (fd < 1)
		return (1);
	bytes_read = read(fd, buffer, 4);
	close(fd);
	if (bytes_read < 4)
		return (1);
	if (buffer[0] == 0x7f && buffer[1] == 'E'
		&& buffer[2] == 'L' && buffer[3] == 'F')
		return (0);
	return (ft_error(shell, BINARY, str), 1);
}

int	no_permission(char *str)
{
	if (access(str, X_OK) == -1)
		return (1);
	return (0);
}
