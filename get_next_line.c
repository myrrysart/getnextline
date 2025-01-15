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
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = buf[i];
		i++;
	}
	return (res);
}

int	fill_node(char *buf)
int newl_check(char *str)
{
	t_strholder	new;
	int	newl_found = 0;
	while (*str && !newl_found)
	{
		if (*str == '\n')
			newl_found = 1;
		str++;
	}
	return (newl_found);
}

	new.str = ft_strdup(buf, ft_strlen(buf) + 1);
	new.next = NULL;
	return (0);
t_strholder	*fill_node(t_strholder *prev, char *buf)
{
	t_strholder	*new;

	if (!prev)
	{
		prev = malloc(sizeof(t_strholder));
		if (!prev)
			return (NULL);
	}
	new = malloc(sizeof(t_strholder));
	if (!new)
		return (NULL);
	prev->next = new;
	new->str = ft_strdup(buf, ft_strlen(buf) + 1);
	new->next = NULL;
	new->newl_exists = newl_check(new->str);
	return (new);
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
char	*next_line_return(t_strholder *head)
{
	char	*s;
	size_t	len;
	size_t	nl_len;

	len = 0;
	nl_len = 0;
	while (head->newl_exists == 0)
	{
		s = malloc(sizeof(char) * (ft_strlen(head->str) + len + 1));
		if (!s)
			return (NULL);
		while (*head->str)
			s[len++] = *(head->str++);
		head = head->next;
	}
	while(head->str[nl_len] != '\n')
		nl_len++;
	s = malloc(sizeof(char) * (nl_len + len + 1));
	s[len + nl_len] = '\0';
	while (nl_len-- > 0)
		s[len + nl_len] = head->str[nl_len];
	return (s);
}

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
