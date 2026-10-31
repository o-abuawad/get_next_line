/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-awa <oabu-awa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 16:54:58 by oabu-awa          #+#    #+#             */
/*   Updated: 2026/10/31 16:54:59 by oabu-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_both(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

static char	*read_str(int fd, char *str)
{
	ssize_t	bytes;
	char	*tmp;

	bytes = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (free_both(str, NULL));
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
			return (free_both(tmp, str));
		tmp[bytes] = '\0';
		str = ft_strjoin(str, tmp);
		if (!str)
			return (free_both(tmp, NULL));
	}
	free(tmp);
	return (str);
}

static char	*get_line(char *str)
{
	char	*tmp;
	size_t	count;
	size_t	i;

	if (!str || !str[0])
		return (NULL);
	count = 0;
	while (str[count] != '\n' && str[count])
		count++;
	if (str[count] == '\n')
		count++;
	tmp = malloc(count + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char	*next_line(char *str)
{
	size_t	count;
	size_t	i;
	char	*tmp;

	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	if (!str[count])
	{
		free(str);
		return (NULL);
	}
	count++;
	tmp = malloc((ft_strlen(str) - count) + 1);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[count])
		tmp[i++] = str[count++];
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_line(str[fd]);
	if (!line)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = next_line(str[fd]);
	return (line);
}
