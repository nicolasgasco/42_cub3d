#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <math.h>

/*ft_calculate_angle will calculate the angle of the ray that
 * is being cast relative to the viewing angle*/

double	ft_calculate_angle(t_map *map)
{
	return (((FIELD_OF_VIEW / 2) - FIELD_OF_VIEW)
		+ (map->column * map->prj->angle_btw_rays));
}

/*ft_set_wall_to_render will compare horizontal & vertical 
 * distances and select the shortest and set wall_to_render
 * with those values*/

void	ft_set_wall_to_render(t_map *map, double dh, double dv)
{
	t_vector	*wall_to_render;

	wall_to_render = malloc (sizeof(t_vector));
	ft_memset(wall_to_render, 0, sizeof(t_vector));
	map->prj->wall_to_render = wall_to_render;
	if (dh > dv)
	{
		map->prj->wall_to_render->x = map->prj->rc_vertical->y;
		map->prj->wall_to_render->y = map->prj->rc_vertical->x;
	}
	else
	{
		map->prj->wall_to_render->x = map->prj->rc_horizontal->x;
		map->prj->wall_to_render->y = map->prj->rc_horizontal->y;
		map->prj->distance_to_wall = dh;
	}
}
