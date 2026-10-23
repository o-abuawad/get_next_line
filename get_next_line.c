/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-awa <oabu-awa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:53:00 by oabu-awa          #+#    #+#             */
/*   Updated: 2026/10/23 19:15:47 by oabu-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_str(int fd, char *str)
{
	ssize_t	bytes;
	char	*tmp;

	bytes = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[bytes] = '\0';
		str = ft_strjoin(str, tmp);
	}
	free(tmp);
	return (str);
}
