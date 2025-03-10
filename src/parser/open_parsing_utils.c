/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 00:40:45 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	handle_exit_err(t_shell *shell, int saved_in, int quote)
{
	dup2(saved_in, 0);
	close(saved_in);
	if (g_sig_type == SIG_C)
	{
		shell->error = 130;
		g_sig_type = 42;
	}
	else
	{
		ft_error(shell, QUOTE_ERR, (char *) &quote);
		close_shell(shell);
	}
	return (0);
}

char	*append_newline(char *str)
{
	char	*new_str;

	new_str = ft_strjoin(str, "\n");
	return (new_str);
}

int	check_close_quotes(char *str, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count % 2);
}

int	quote_is_open(char *str)
{
	int	i;
	int	sq;
	int	dq;

	dq = 0;
	sq = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == DQ && dq)
			dq = 0;
		else if (str[i] == DQ && !sq)
			dq = 1;
		else if (str[i] == SQ && sq)
			sq = 0;
		else if (str[i] == SQ && !dq)
			sq = 1;
	}
	if (sq)
		return (SQ);
	else if (dq)
		return (DQ);
	return (0);
}
