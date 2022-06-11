#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_validate_size(t_map *map)
{
	if (map->height < 3)
		ft_print_error_exit(map,
			"Error. Incorrect map size: height must be over 3 rows", 11);
	if (map->width < 3)
		ft_print_error_exit(map,
			"Error. Incorrect map size: width must be over 3 columns", 12);
}
