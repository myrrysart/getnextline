#!/bin/bash

FILE=$1
NUMBER=$2

cat << EOF > main.c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	file=open("$FILE", O_RDONLY);
	int	x=$NUMBER;
	while(x-- > 0)
		printf("%s", get_next_line(file));
	return (0);
}
EOF

cc -g -Wall -Wextra -Werror main.c get_next_line.c -o get_next_line_test
./get_next_line_test
