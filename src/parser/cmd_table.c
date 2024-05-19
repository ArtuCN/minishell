/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:44:34 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/19 18:14:44 by aconti           ###   ########.fr       */
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

int there_is_redir(t_token *token)
{
	int	i;

	i = -1;
	while (token->tokens[++i])
	{
		if (token->tokens[i] == 'O' || token->tokens[i] == 'I' || token->tokens[i] == 'A')
			return (1);
	}
	return (0);
}

int add_redir(t_shell *shell, t_cmd *cmd_table)
{
	t_token *token;
	int		i;
	int		j;
	
	j = 0;
	i = -1;
	token = shell->tokens;
	while(token->tokens[++i])
	{
		if (token->tokens[i] == 'O' || token->tokens[i] == 'I' || token->tokens[i] == 'A')
		{
			cmd_table->red = malloc(sizeof(t_red));
			if (!cmd_table->red)
				return (0);
			cmd_table->red->redir = token->index[i];
			cmd_table->red->file = token->index[i + 1];
			token->tokens[i] = 'X';
			token->tokens[i + 1] = 'X';
		}
	}
	return (1);
}

int put_this(t_shell *shell, t_cmd *cmd_table, char type)
{
	t_token *token;
	int		i;
	
	i = 0;
	token = shell->tokens;
	while (token->tokens[i] != type && token->tokens[i])
		i++;
	if (token->tokens[i] == type)
	{
		cmd_table->command = token->index[i];
		cmd_table->cmd_arg = ft_calloc(sizeof(char *), 2 + 1);
		if (!cmd_table->cmd_arg)
			return (0);
		cmd_table->cmd_arg[0] = token->index[i];
		if (token->index[i + 1] && token->tokens[i + 1] == 'S')
			cmd_table->cmd_arg[1] = token->index[i + 1];
	}
	shell->tokens->tokens[i] = 'X';
	if (token->tokens[i + 1] == 'S')
		shell->tokens->tokens[i + 1] = 'X';
	if (there_is_redir(token))
		add_redir(shell, &cmd_table[i]);
	return (1);
}

int only_x(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 'X')
			return (0);
	return (1);
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
			put_this(shell, &cmd_table[j], 'H');
		else if (find_token(input_args, 'C'))
			put_this(shell, &cmd_table[j], 'C');
		j++;
	}
	return (1);
}

void print_cmd_tab(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->cmd_table[++i] != NULL)
			printf("command table n %d, command = %s", i, shell->cmd_table[i].command);
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
	printf("1 %s\n", shell->tokens->tokens);
	// printf("1 %s %s \n", shell->cmd_table[0].cmd_arg[0], shell->cmd_table[0].cmd_arg[1]);
	// printf("1 %s %s \n", shell->cmd_table[1].cmd_arg[0], shell->cmd_table[1].cmd_arg[1]);
	// printf("1 %s %s \n", shell->cmd_table[2].cmd_arg[0], shell->cmd_table[2].cmd_arg[1]);
	print_cmd_tab(shell);
	return (1);
}
