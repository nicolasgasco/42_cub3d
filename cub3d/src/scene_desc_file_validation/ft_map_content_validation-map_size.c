#include "../cub3d.h"

void	ft_validate_size(t_map *map)
{
    if (map->height < 3)
    {
        printf("Error. Incorrect map size: height must be over 3 rows\n");
	exit(11);
    }
    if (map->width < 3)
    {
	printf("Error. Incorrect map size: width must be over 3 columns\n");
	exit(12);
    }
}
