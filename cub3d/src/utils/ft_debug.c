#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_write_debug_msg(char *msg)
{
    int fd;

    fd = open("./tests/scripts/debug_output", O_WRONLY|O_TRUNC);
    write(fd, msg, ft_strlen(msg) + 1);
    close(fd);
}
