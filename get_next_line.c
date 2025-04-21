/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:40:00 by jyniemit          #+#    #+#             */
/*   Updated: 2025/04/21 18:21:30 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	safe_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*extract_line(char **remains)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*remains || !**remains)
	{
		safe_free((void *)remains);
		return (NULL);
	}
	newline_pos = ft_strchr(*remains, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remains, 0, newline_pos - *remains + 1);
		temp = ft_strdup(newline_pos + 1);
		safe_free((void *)remains);
		*remains = temp;
	}
	else
	{
		line = ft_strdup(*remains);
		safe_free((void *)remains);
	}
	return (line);
}

static int	gnl_safety_check(char **remains, char *buffer, int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (*remains)
			safe_free((void *)remains);
		safe_free((void *)&buffer);
		return (-1);
	}
	return (0);
}

static int	read_to_remains(char **remains, char *buffer, int fd)
{
	int		bytes_read;
	char	*temp;
	int		continue_reading;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	continue_reading = 1;
	while (bytes_read > 0 && continue_reading)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*remains, buffer);
		if (!temp)
			return (-1);
		*remains = temp;
		if (ft_strchr(*remains, '\n'))
			continue_reading = 0;
		else
			bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*remains = NULL;
	char		*buffer;
	char		*line;
	int			bytes_read;

	bytes_read = 0;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (gnl_safety_check(&remains, buffer, fd) == -1)
		return (NULL);
	if (!remains)
		remains = ft_strdup("");
	bytes_read = read_to_remains(&remains, buffer, fd);
	if (bytes_read < 0)
		safe_free((void *)&remains);
	line = extract_line(&remains);
	if (!line && !remains)
	{
		safe_free((void *)&buffer);
		return (NULL);
	}
	safe_free((void *)&buffer);
	return (line);
}
