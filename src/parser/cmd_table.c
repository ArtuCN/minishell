/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/15 13:15:14 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pipe_pos(t_token *token, int start)
{
	int	i;
	int	j;
	int	curr_pipe;

	curr_pipe = 0;
	j = -1;
	i = 0;
	while (token->tokens[++j] && curr_pipe != start)
	{
		if (token->tokens[j] == PIPE)
		{
			i = j;
			curr_pipe++;
		}
	}
	return (i);
}

int	find_token(char *tokens, char type)
{
	int	i;

	i = -1;
	while (tokens[++i])
	{
		if (tokens[i] == type)
			return (1);
	}
	return (0);
}

int	check_tokens(t_shell *shell, t_cmd *cmd_table, char *input_args)
{
	int	i;
	int	j;
	
	j = 0;
	i = -1;
	while (input_args[++i])
	{
		if (find_token(input_args, 'H'))
			find_start_pos(cmd_table[j++], 'H', shell, i);
	}
	return (1);
}
int	count_tkn(char *input_args)
{
	int	i;
	int	count;
	int	found;

	count = 0;
	i = -1;
	found = 0;
	while (input_args[++i])
	{
		if (input_args[i] == 'C' || input_args[i] == 'H')
		{
			found = 1;
			count++;
		}
	}
	if (found == 0)
		count++;
	return (count);
}

int	init_cmd_table(t_shell *shell)
{
	t_token 	*token;
	char		**input_args;
	int			len;
	int			i;
	
	len = 0;
	token = shell->tokens;
	input_args = ft_split(token->tokens, 'P');
	i = -1;
	while (input_args[++i])
		len += count_tkn(input_args[i]);
	shell->cmd_table = malloc(sizeof(t_cmd) * len);
	if (!shell->cmd_table)
		return (0);
	i = -1;
	while (input_args[++i])
		check_tokens(shell, shell->cmd_table, input_args[i]);
	collect_garbage(shell, 0, input_args);
	print_cmd(shell, len);
	return (1);
}
