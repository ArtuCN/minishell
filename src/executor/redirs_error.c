/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:48:18 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[i] == ' ')
		i++;
	return (str + i);
}

int	parse_redirs(t_shell *shell, t_table table)
{
	int	i;

	i = -1;
	while (++i < matrix_len(table.redirs))
	{
		if (table.fd[i] == -1)
			return (ft_error(shell, OPEN_ERR, skip_space(table.redirs[i])));
	}
	return (1);
}
