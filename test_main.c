#include "get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    char *line;

    if (argc != 2)
        return (1);
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        free(line);
    }
    close(fd);
    return (0);
}
