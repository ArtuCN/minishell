/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:24:37 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	int		i;
	int		n;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = -1;
	newstr = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (newstr == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		newstr[i] = s1[i];
	n = i;
	i = -1;
	while (s2[++i] != '\0')
		newstr[n + i] = s2[i];
	newstr[n + i] = '\0';
	return (newstr);
}
