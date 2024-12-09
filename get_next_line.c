/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:42:35 by Jyniemit          #+#    #+#             */
/*   Updated: 2024/12/05 14:43:39 by Jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (*(s++))
		len++;
	return (len);
}

char	*ft_strdup(char *buf, size_t len)
{
	return (NULL);
}

int	fill_node(char *buf)
{
	t_strholder	new;

	new.str = ft_strdup(buf, ft_strlen(buf) + 1);
	new.next = NULL;
	return (0);
}

//char	*get_next_line(int fd)
//{
//	char	*buf;
//
//	buf = malloc(BUFFER_SIZE + 1);
//	if (!buf)
//		return (NULL);
//	read(open(argv[1], O_RDONLY), buf, READ_SIZE);
//	if (fill_node(buf))
//		return (NULL);
//	return (buf);
//}


int	main(int argc, char **argv)
{
	char	*buf;

	if (argc != 2)
		return (1);
	if (read(open(argv[1], O_RDONLY), 0, 0))
		return (1);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (1);
	read(open(argv[1], O_RDONLY), buf, READ_SIZE);
	printf("-------- |%s| --------", buf);
	free(buf);
	return (0);
}
