/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:43 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_redirs(int *red, int len)
{
	int	i;

	i = -1;
	if (!len)
		return ;
	while (++i < len)
		if (red[i] > 2)
			close(red[i]);
}

int	find_space(char *index)
{
	int	i;

	i = 0;
	while (index[i] != SPACE)
		i++;
	if (!index[i])
		return (0);
	return (1);
}

void	free_matrix(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
	mat = NULL;
}

void	sig_handle(t_shell *shell)
{
	if (g_sig_type == SIG_C)
		shell->error = 130;
	else if (g_sig_type == CORE_DUMPED)
		shell->error = 131;
}

int	ft_isspace(int c)
{
	if (c == 32 || c == '\t')
		return (1);
	return (0);
}
