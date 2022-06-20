#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <math.h>

/*ft_calculate_wall_height will calculate the wall height
 * based on the correct distance to the intersection*/

int	ft_calculate_wall_height(t_map *map)
{
	int		beta;
	double	correct_distance;
	int		height;

	beta = ft_calculate_angle(map);
	correct_distance = map->prj->distance_to_wall * cos(beta * (PI / 180));
	height = (int)(round(CUBE_SIZE / correct_distance
				* map->prj->distance_to_pp));
	printf("The height of the wall at column %d is %d\n", map->column, height);
	return (height);
}

/*ft_fill_slice will fill each variable of the slice*/

void	ft_fill_slice(t_map *map)
{
	map->slc->column = map->column;
	map->slc->height = ft_calculate_wall_height(map);
//	map->slc->texture = ft_set_texture(map);
//	map->slc->wall_x = ft_calculate_wall_x(map);
}

/*ft_raycast_to_slice will perform calculations to 
 * provide the data per slice for rendering*/

void	ft_raycast_to_slice(t_map *map, t_view *view)
{
	t_slice	*slice;

	slice = malloc (sizeof(t_slice));
	ft_memset(slice, 0, sizeof(t_slice));
	map->slc = slice;
	ft_fill_slice(map);
	//Render entry point --> Nico
	ft_render_column(view, map);
}
