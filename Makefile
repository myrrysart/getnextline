# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 07:33:36 by Jyniemit          #+#    #+#              #
#    Updated: 2024/12/05 07:44:31 by Jyniemit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#TEST#
NAME = get_next_line 
#TEST#
FLAG = -Wall -Wextra -Werror -g
#TESTE#
BUFFER = -D BUFFER_SIZE=10
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
	
