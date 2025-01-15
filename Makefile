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

NAME = get_next_line 
FLAG = -Wall -Wextra -Werror
DFLAG = -g
BUFFER = -D BUFFER_SIZE=10
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)
HEADER = get_next_line.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	cc $(FLAG) -c $< -o $@

debug: FLAG+=$(DFLAG) 
debug: all
	touch .debug

clean:
	rm -f *.o

fclean: clean
	rm -f .debug
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re debug %.o
