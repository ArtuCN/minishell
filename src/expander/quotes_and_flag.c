/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:22:43 by adonato           #+#    #+#             */
/*   Updated: 2024/07/09 15:48:31 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	assign_flag(t_token *token, int j, int i)
{
	if (token->index[token->wrd][i] == '>'
		|| token->index[token->wrd][i] == '<')
		token->flag[token->wrd] = '1';
	else if (j == 5)
		token->flag[token->wrd] = '2';
	else if (token->index[token->wrd][i] == '\0')
		token->flag[token->wrd] = '0';
	return (token->flag[token->wrd]);
}

char	*check_flag(t_token *token)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (token->index[token->wrd][++i])
	{
		if (token->index[token->wrd][i] == SQ
			|| token->index[token->wrd][i] == DQ)
		{
			while (token->index[token->wrd][++i] != '>'
				&& token->index[token->wrd][i] != '<'
				&& token->index[token->wrd][i])
				;
			j = 5;
			break ;
		}
	}
	token->flag[token->wrd] = assign_flag(token, j, i);
	return (token->flag);
}

int	count_quotes(t_token *token)
{
	int		i;
	int		quote_nbr;

	i = 0;
	quote_nbr = 0;
	while (token->index[token->wrd][i++])
	{
		if (token->index[token->wrd][i] == SQ)
		{
			while (token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != SQ)
				;
			quote_nbr += 2;
		}
		else if (token->index[token->wrd][i] == DQ)
		{
			while (token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != DQ)
				;
			quote_nbr += 2;
		}
	}
	return (i - quote_nbr);
}

char	*remove_quotes(t_shell *shell, t_token *token, int i)
{
	int		j;
	char	*temp;

	j = 0;
	temp = ft_calloc(sizeof(char *), i + 1);
	if (!temp)
		return (0);
	i = -1;
	while (token->index[token->wrd][++i])
	{
		if (token->index[token->wrd][i] == SQ)
			while (token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != SQ)
				temp[j++] = token->index[token->wrd][i];
		else if (token->index[token->wrd][i] == DQ)
			while (token->index[token->wrd][++i]
				&& token->index[token->wrd][i] != DQ)
				temp[j++] = token->index[token->wrd][i];
		else if (token->index[token->wrd][i])
			temp[j++] = token->index[token->wrd][i];
		if (!token->index[token->wrd][i])
			break ;
	}
	collect_garbage(shell, token->index[token->wrd], 0);
	return (temp);
}
