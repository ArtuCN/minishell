/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:40:50 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_command(char *str)
{
	int		i;
	char	*copy;
	int		count;
	int		j;

	count = 0;
	i = -1;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	while (!ft_isspace(str[i]))
	{
		count++;
		i++;
	}
	copy = ft_calloc(sizeof(char *), count + 1);
	if (!copy)
		return (0);
	i = -1;
	while (j++ < count)
		copy[++i] = str[j];
	if (is_builtin(copy))
		return (free(copy), 1);
	return (0);
}
