/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:59:01 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	set_token(t_shell *shell, t_token *token, int *i, int *command)
{
	if (find_cmd_path(shell, token->index[*i], *i) && *command == 0)
	{
		*command = 1;
		token->tokens[*i] = 'C';
	}
	else if (!(ft_strncmp(token->index[*i], "<<", 2)) && token->flag[*i] == '0')
		token->tokens[*i] = 'H';
	else if (!(ft_strncmp(token->index[*i], ">>", 2)) && token->flag[*i] == '0')
		token->tokens[*i] = 'A';
	else if (!(ft_strncmp(token->index[*i], ">", 1)) && token->flag[*i] == '0')
		token->tokens[*i] = 'O';
	else if (!(ft_strncmp(token->index[*i], "<", 1)) && token->flag[*i] == '0')
		token->tokens[*i] = 'I';
	else if ((ft_strncmp(token->index[*i], "||", 2) == 0
			&& token->flag[*i] == '0'))
		return (ft_error(shell, SYNTAX, "|"));
	else if (token->index[*i][0] == '|' && token->flag[*i] == '0')
	{
		*command = 0;
		token->tokens[*i] = 'P';
	}
	else
		token->tokens[*i] = 'S';
	return (1);
}

int	tokenizer(t_shell *shell)
{
	t_token	*token;
	int		i;
	int		command;

	command = 0;
	token = shell->tokens;
	token->tokens = ft_calloc(sizeof(char *), matrix_len(token->index) + 1);
	if (!token->tokens)
		return (0);
	collect_garbage(shell, token->tokens, 0);
	i = -1;
	while (token->index[++i])
		if (!set_token(shell, token, &i, &command))
			return (0);
	command = 0;
	return (1);
}
