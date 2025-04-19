/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:18:54 by Jyniemit          #+#    #+#             */
/*   Updated: 2025/01/16 08:22:19 by Jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    GET_NEXT_LINE_H
# define    GET_NEXT_LINE_H
# ifndef    BUFFER_SIZE
# define    BUFFER_SIZE 100
# endif
# define    NL_FLAG (1 << 0)
# define    EOF_FLAG (1 << 1)
//read & close
# include <unistd.h>
//malloc
# include <stdlib.h>
//typedefs for [u]int##_t and MAX/MIN values
# include <stdint.h>
char	*get_next_line(int fd);

#endif
