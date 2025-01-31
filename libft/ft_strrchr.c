/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconti <aconti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:20:23 by aconti            #+#    #+#             */
/*   Updated: 2024/07/09 15:47:15 by aconti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*s_start;

	i = -1;
	s_start = s;
	while (s[++i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			s += i;
			i = 0;
		}
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	if (s_start == s && (unsigned char)*s_start != (unsigned char)c)
		return (NULL);
	return ((char *)s);
}
