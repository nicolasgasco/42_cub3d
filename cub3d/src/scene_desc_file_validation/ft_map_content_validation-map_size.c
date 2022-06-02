#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_validate_size(t_map *map)
{
    if (map->height < 3)
    {
        ft_free_allocated_map_data(map);
        ft_free_map_struct(map);
        ft_putendl_fd("Error. Incorrect map size: height must be over 3 rows", STDERR_FILENO);
	exit(11);
    }
    if (map->width < 3)
    {
        ft_putendl_fd("Error. Incorrect map size: width must be over 3 columns", STDERR_FILENO);
	exit(12);
    }
}
