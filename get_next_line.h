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
//read & close
# include <unistd.h>
//malloc
# include <stdlib.h>

char	*get_next_line(int fd);

#endif
