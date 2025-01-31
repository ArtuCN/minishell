/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:49:15 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_words(char *str)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] == 32)
		i++;
	while (str[i])
	{
		while (str[i] == 32)
			i++;
		if (str[i])
			words++;
		while (str[i] != 32 && str[i])
			i++;
	}
	return (words);
}
