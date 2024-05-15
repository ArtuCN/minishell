/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:32:57 by ciusca            #+#    #+#             */
/*   Updated: 2024/05/10 16:58:04 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


t_garbage *new_node(char *arg, char **mat)
{
	t_garbage *node;
	
	node = malloc(sizeof(t_garbage));
	if (!node)
		return (0);
	node->arg = arg;	
	node->mat = mat;
	node->next = NULL;
	return (node);
}

int	collect_garbage(t_shell *shell, char *arg, char **mat)
{
	t_garbage *collect;
	
	collect = shell->collector;
	while (collect->next)
		collect = collect->next;
	collect->next = new_node(arg, mat);
	return (1);
}
void	close_shell(t_shell *shell)
{
	t_garbage *garbage;
	t_garbage *temp;

	garbage = shell->collector;
	temp = garbage->next;
	free(shell->tokens);
	free(garbage);
	///free_cmd_table(shell);
	garbage = NULL;
	garbage = temp;
	while (garbage)
	{
		if (garbage->arg)
			free(garbage->arg);
		if (garbage->mat)
			free_matrix(garbage->mat);
		temp = garbage->next;
		free(garbage);
		garbage = temp;
	}
	exit(errno);
}
