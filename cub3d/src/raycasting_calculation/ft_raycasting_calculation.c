#include "../cub3d.h"
#include <math.h>

/*ft_horizontal_intersection will find the hit(s) with the
 * horizontal axis of the map until there is a wall*/

void	ft_horizontal_intersection(t_map *map)
{
	double	increment_y;
	double	increment_x;
	int		x;
	int		y;

	ft_set_coords_angle_direction_horizontal(map);
	if (map->prj->view_angle > 0 && map->prj->view_angle < 180)
		increment_y = (CUBE_SIZE) * (-1);
	else
		increment_y = CUBE_SIZE;
	increment_x = CUBE_SIZE / tan(map->prj->view_angle * (PI / 180));
	y = floor(map->prj->rc_horizontal->y / CUBE_SIZE);
	x = floor(map->prj->rc_horizontal->x / CUBE_SIZE);
	while (map->map_content[y][x] != '1')
	{
		map->prj->rc_horizontal->y += increment_y;
		map->prj->rc_horizontal->x += increment_x;
		y = floor(map->prj->rc_horizontal->y / CUBE_SIZE);
		x = floor(map->prj->rc_horizontal->x / CUBE_SIZE);
	}
	printf("HORIZONTAL: El %c está en la posición [%i][%i]\n",
		map->map_content[y][x], y, x);
}

/*ft_vertical_intersection will find the hit(s) with the
 * vertical axis of the map until there is a wall*/

void	ft_vertical_intersection(t_map *map)
{
	double	increment_y;
	double	increment_x;
	int		x;
	int		y;

	ft_set_coords_angle_direction_vertical(map);
	if (map->prj->view_angle < 270 && map->prj->view_angle < 90)
		increment_x = CUBE_SIZE * -1;
	else
		increment_x = (CUBE_SIZE);
	increment_y = CUBE_SIZE * tan(map->prj->view_angle * (PI / 180));
	y = floor(map->prj->rc_vertical->y / CUBE_SIZE);
	x = floor(map->prj->rc_vertical->x / CUBE_SIZE);
	printf("X: %f, x: %d, Y: %f, y: %d\n", map->prj->rc_vertical->x,
		x, map->prj->rc_vertical->y, y);
	while (map->map_content[y][x] != '1')
	{
		map->prj->rc_vertical->y += increment_y;
		map->prj->rc_vertical->x += increment_x;
		y = floor(map->prj->rc_vertical->y / CUBE_SIZE);
		x = floor(map->prj->rc_vertical->x / CUBE_SIZE);
	}
	printf("VERTICAL: El %c está en la posición [%i][%i]\n",
		map->map_content[y][x], y, x);
}

/*ft_get_ray_angle will calculate and set map->prj->Po
 * with the viewing angle for the column to raycast*/

void	ft_get_ray_angle(t_map *map, int column)
{
	double	deviance;

	map->prj->view_angle = ft_set_viewing_angle(map->prj->player_orientation)
		- (FIELD_OF_VIEW / 2);
	if (map->prj->view_angle < 0)
		map->prj->view_angle += 360;
	deviance = (column + 1) * map->prj->angle_btw_rays;
	map->prj->view_angle += deviance;
}

void	ft_raycasting_calculation(t_map *map)
{
	int	column;

	printf("Px: %f, Py: %f, PO: %c\n, view_angle: %f, distance: %f, angle: %f\n",
		map->prj->player->x, map->prj->player->y, map->prj->player_orientation,
		map->prj->view_angle, map->prj->distance_to_pp,
		map->prj->angle_btw_rays);
	ft_convert_to_cube_position(map);
	column = 0;
	while (column < PROJ_PLANE_WIDTH)
	{
		ft_get_ray_angle(map, column);
		ft_horizontal_intersection(map);
		ft_vertical_intersection(map);
		column++;
	}
}
