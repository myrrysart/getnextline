/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:50:50 by Jyniemit          #+#    #+#             */
/*   Updated: 2025/04/19 17:53:38 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

uint8_t	read_into_buffer(int fd, uint8_t *buf);
uint8_t check_buf(uint8_t *buf);
uint8_t	fill_str(uint8_t **str, uint8_t *buf, uint8_t status);
void	buffer_flushing(uint8_t *buf, size_t cut_index);

char	*get_next_line(int fd)
{
	static uint8_t	buf[BUFFER_SIZE];
	uint8_t			*str;
	uint8_t			status;
	
	status = 0;
	str = NULL;
	if (!*buf)
	{
		if (read_into_buffer(fd, buf))
			return (NULL);
	}
	status = check_buf(buf);
	while (status == 0)
	{
		if (read_into_buffer(fd, buf))
			return (NULL);
		status = check_buf(buf);
	}
	if (fill_str(&str, buf, status))
		return (NULL);
	return ((char *)str);
}

uint8_t	read_into_buffer(int fd, uint8_t *buf)
{
	size_t	i;

	i = 0;
	(void)i;
	buf = malloc()
	if (read(fd, buf, BUFFER_SIZE) == -1)
		return (1);
	return (0);
}

uint8_t	check_buf(uint8_t *buf)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i++] == '\n')
			return (NL_FLAG);
	}
	return (EOF_FLAG);
}

uint8_t	fill_str(uint8_t **str, uint8_t *buf, uint8_t status)
{
	size_t	i;
	size_t	cut_index;

	i = 0;
	while(buf[i] != '\n' && buf[i] != '\0')
		i++;
	cut_index = i;
	*str = malloc(sizeof(uint8_t) * (i + 1));
	if (!*str)
	{
		return (1);
	}
	if (status & NL_FLAG)
		(*str)[i] = '\n';
	else
		(*str)[i] = '\0';
	while (i-- > 0)
		(*str)[i] = buf[i];
	buffer_flushing(buf, cut_index);
	return (0);
}

void	buffer_flushing(uint8_t *buf, size_t cut_index)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = cut_index + 1;
	while (buf[j] != '\0')
	{
		buf[i] = buf[j];
		i++;
		j++;
	}
	while (buf[i] != '\0')
		buf[i++] = '\0';
}
