/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	fill_fds(t_token *token, t_table *table)
{
	int		i;
	int		end;
	int		j;

	j = 0;
	i = 0;
	while (token->redirs[i] == -42)
		i++;
	end = matrix_len(table->redirs) + i;
	while (i < end)
	{
		table->fd[j++] = token->redirs[i];
		token->redirs[i] = -42;
		i++;
	}
	return (1);
}
