/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-awa <oabu-awa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:55:13 by oabu-awa          #+#    #+#             */
/*   Updated: 2026/10/31 16:55:13 by oabu-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != (char)c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

static char	*counter(char *str1, char *str2, char *ptr)
{
	int	i1;
	int	j1;

	i1 = 0;
	if (str1)
	{
		while (str1[i1])
		{
			ptr[i1] = str1[i1];
			i1++;
		}
	}
	j1 = 0;
	while (str2[j1])
	{
		ptr[i1] = str2[j1];
		i1++;
		j1++;
	}
	ptr[i1] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*n;
	size_t	total_len;

	if (!s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	n = malloc(total_len + 1);
	if (!n)
	{
		free(s1);
		return (NULL);
	}
	n = counter(s1, s2, n);
	free(s1);
	return (n);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
