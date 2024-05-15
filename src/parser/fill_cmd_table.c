/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:09:43 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/15 13:17:40 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_cmd(t_shell *shell, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		printf("redir = %s, %s\n", shell->cmd_table[i].red->file, shell->cmd_table[i].red->redir);
	}
}

int	fill_cmd(t_cmd cmd, t_shell *shell, int i)
{
	t_token *token;

	token = shell->tokens;
	printf("ciao\n");
	if (is_redir(token->tokens[i]))
	{
		cmd.red = malloc(sizeof(t_red));
		token->tokens[i] = 'X';
		token->tokens[i + 1] = 'X';
		cmd.red->file = token->index[i + 1];
		cmd.red->redir = token->index[i];
		cmd.cmd_arg = 0;
		cmd.command = 0;
		cmd.pathname = 0;
	}
	return (1);
}

int	find_start_pos(t_cmd cmd, int type, t_shell *shell, int start)
{
	int	i;
	t_token	*token;
	(void)cmd;
	token = shell->tokens;
	i = pipe_pos(token, start);
	while (token->tokens[i] || token->tokens[i] != PIPE)
	{
		if (token->tokens[i] == type)
			fill_cmd(cmd, shell, i);
		i++;
	}	
	return(1);
}
