#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int fd = open("test6", O_RDONLY);
	if (fd == -1)
		return (1);
	size_t	j = 1;
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%zu:%s", j++, line);
		free(line);
	}
	close(fd);
	return (0);
}
