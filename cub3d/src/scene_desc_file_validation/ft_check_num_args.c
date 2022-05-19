#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_check_num_args(int argc)
{
    if (argc != 2)
    {
        ft_putendl_fd("Error: arguments", STDERR_FILENO);
        exit(1);
    }
}