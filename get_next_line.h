/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 09:45:19 by Jyniemit          #+#    #+#             */
/*   Updated: 2024/12/05 14:42:43 by Jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    GET_NEXT_LINE_H
# define    GET_NEXT_LINE_H

# ifndef    READ_SIZE
#  define    READ_SIZE 8
# endif

# ifndef    BUFFER_SIZE
#  define    BUFFER_SIZE 8
# endif

# include <stdio.h> //test
# include <fcntl.h> //test

/* read() */
# include <unistd.h>
/* malloc() & free() */
# include <stdlib.h>

typedef struct s_strholder
{
	char				*str;
	struct s_strholder	*prev;
	struct s_strholder	*next;
} t_strholder;

char	*get_next_line(int fd);
#endif
