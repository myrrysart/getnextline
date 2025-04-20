/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:55:35 by jyniemit          #+#    #+#             */
/*   Updated: 2025/04/20 18:22:54 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// Helper function to extract part of string with specified length

static char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *substr;
    size_t i;
    
    if (!s)
        return (NULL);
        
    substr = malloc(len + 1);
    if (!substr)
        return (NULL);
        
    i = 0;
    while (i < len && s[start + i])
    {
        substr[i] = s[start + i];
        i++;
    }
    substr[i] = '\0';
    
    return (substr);
}



char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	joined = (char *)malloc(i + j + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	free(s1);
	return (joined);
}

char *extract_line(char **remains)
{
    char *line;
    char *newline_pos;
    char *temp;
    
    if (!*remains || !**remains)
    {
        free(*remains);
        *remains = NULL;
        return (NULL);
    }
    
    newline_pos = ft_strchr(*remains, '\n');
    if (newline_pos)
    {
        // Extract up to and INCLUDING the newline
        line = ft_substr(*remains, 0, newline_pos - *remains + 1);
        
        // Save what's left for next call
        temp = ft_strdup(newline_pos + 1);
        free(*remains);
        *remains = temp;
    }
    else
    {
        line = ft_strdup(*remains);
        free(*remains);
        *remains = NULL;
    }
    
    return (line);
}
