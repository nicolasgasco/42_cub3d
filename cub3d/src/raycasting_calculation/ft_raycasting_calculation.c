#include "../cub3d.h"
#include <math.h>

/*ft_calculate_distance will calculate the distances from 
 * the player to the horizontal & vertical intersections.*/

void	ft_calculate_distance(t_map *map)
{
	double		distance_horizontal;
	double		distance_vertical;

	printf("-->HORIZONTAL<--Px: %f, rchx: %f, view_angle: %f\n",
		map->prj->player->x, map->prj->rc_horizontal->x, map->prj->view_angle);
	distance_horizontal = fabs(map->prj->player->x - map->prj->rc_horizontal->x)
		/ cos(map->prj->view_angle * (PI / 180));
	if (distance_horizontal <= 0)
		distance_horizontal = fabs(map->prj->player->y
				- map->prj->rc_horizontal->y)
			/ sin(map->prj->view_angle * (PI / 180));
	printf("-->VERTICAL>--Px: %f, rcvx: %f, view_angle: %f\n",
		map->prj->player->x, map->prj->rc_horizontal->x, map->prj->view_angle);
	distance_vertical = fabs(map->prj->player->x - map->prj->rc_vertical->y)
		/ cos(map->prj->view_angle * (PI / 180));
	if (distance_vertical <= 0)
		distance_vertical = fabs(map->prj->player->y
				- map->prj->rc_horizontal->y)
			/ sin(map->prj->view_angle * (PI / 180));
	ft_set_wall_to_render(map, distance_horizontal, distance_vertical);
}

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
	while (y >= 0 && x >= 0 && y < map->height && x < map->width && map->map_content[y][x] != '1')
	{
		map->prj->rc_horizontal->y += increment_y;
		map->prj->rc_horizontal->x += increment_x;
		y = floor(map->prj->rc_horizontal->y / CUBE_SIZE);
		x = floor(map->prj->rc_horizontal->x / CUBE_SIZE);
	}
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
	while (y >= 0 && x >= 0 && y < map->height && x < map->width && map->map_content[y][x] != '1')
	{
		map->prj->rc_vertical->y += increment_y;
		map->prj->rc_vertical->x += increment_x;
		y = floor(map->prj->rc_vertical->y / CUBE_SIZE);
		x = floor(map->prj->rc_vertical->x / CUBE_SIZE);
	}
}

/*ft_get_ray_angle will calculate and set map->prj->Po
 * with the viewing angle for the column to raycast*/

void	ft_get_ray_angle(t_map *map)
{
	double	deviance;

	map->prj->view_angle = ft_set_viewing_angle(map->prj->player_orientation)
		- (FIELD_OF_VIEW / 2);
	if (map->prj->view_angle < 0)
		map->prj->view_angle += 360;
	deviance = map->column * map->prj->angle_btw_rays;
	map->prj->view_angle += deviance;
}

/*ft_raycasting_calculation initializes the loop to
 * calculate & render the rays or slices.*/

void	ft_raycasting_calculation(t_map *map)
{
	ft_convert_to_cube_position(map);
	map->column = 0;
	while (map->column < PROJ_PLANE_WIDTH)
	{
		ft_get_ray_angle(map);
		ft_horizontal_intersection(map);
		ft_vertical_intersection(map);
		ft_calculate_distance(map);
		ft_raycast_to_slice(map);
		printf("Wtr y: %f, wtr x: %f\nDistance: %f\n",
			map->prj->wall_to_render->y, map->prj->wall_to_render->x,
			map->prj->distance_to_wall);
		ft_free_raycast_data(map);
		map->column++;
	}
}
