/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:34:56 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	parse_heredoc(t_shell *shell, t_token *token)
{
	int	i;

	i = -1;
	while (token->tokens[++i])
	{
		if (token->tokens[i] == 'H')
		{
			token->redirs[i + 1] = ft_heredoc(shell, token, i + 1);
			if (!token->redirs[i + 1])
				return (0);
		}
	}
	return (1);
}

int	open_files(t_token *token, int i)
{
	int	fd;

	fd = 0;
	if (token->tokens[i - 1] == 'I')
		fd = open(token->index[i], O_RDONLY);
	else if (token->tokens[i - 1] == 'A')
		fd = open(token->index[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (token->tokens[i - 1] == 'O')
		fd = open(token->index[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (token->tokens[i - 1] == 'H')
		fd = token->redirs[i];
	token->redirs[i] = fd;
	return (1);
}

int	open_redirs(t_token *token)
{
	int	i;

	i = -1;
	while (token->tokens[++i])
	{
		if (is_redir(token->tokens[i]))
			if (!open_files(token, i + 1))
				return (0);
	}
	return (1);
}

int	count_redirs(char *tokens)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (tokens[++i])
		if (is_redir(tokens[i]))
			count++;
	return (count);
}

int	find_redirs(t_shell *shell)
{
	t_token	*token;
	int		i;

	i = -1;
	token = shell->tokens;
	token->redirs = malloc(sizeof(int) * ft_strlen(token->tokens));
	while (++i < (int)ft_strlen(token->tokens))
		token->redirs[i] = -1;
	collect_garbage(shell, (char *)token->redirs, 0);
	if (!parse_heredoc(shell, token))
	{
		return (0);
	}
	if (!open_redirs(token))
	{
		return (0);
	}
	return (1);
}
