/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_calculation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:56:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/07/10 20:06:21 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

/*ft_calculate_distance will calculate the distances from 
 * the player to the horizontal & vertical intersections.*/

void	ft_calculate_distance(t_map *map)
{
	double		distance_horizontal;
	double		distance_vertical;

	distance_horizontal = sqrt((map->prj->rc_horizontal->x
				- map->prj->player->x)
			* (map->prj->rc_horizontal->x - map->prj->player->x)
			+ (map->prj->rc_horizontal->y - map->prj->player->y)
			* (map->prj->rc_horizontal->y - map->prj->player->y));
	printf("%f, %f\n", map->prj->rc_horizontal->y, map->prj->rc_horizontal->x);
	printf("[%d][%d]\n", ((int)(map->prj->rc_horizontal->y / CUBE_SIZE)),
		((int)(map->prj->rc_horizontal->x / CUBE_SIZE)));
	distance_vertical = sqrt((map->prj->rc_vertical->x - map->prj->player->x)
			* (map->prj->rc_vertical->x - map->prj->player->x)
			+ (map->prj->rc_vertical->y - map->prj->player->y)
			* (map->prj->rc_vertical->y - map->prj->player->y));
	printf("%f, %f\n", map->prj->rc_vertical->y, map->prj->rc_vertical->x);
	printf("[%d][%d]\n", ((int)(map->prj->rc_vertical->y / CUBE_SIZE)),
		((int)(map->prj->rc_vertical->x / CUBE_SIZE)));
	ft_set_wall_to_render(map, distance_horizontal, distance_vertical);
	printf("Horizontal distance: %f\nVertical distance: %f\n",
		distance_horizontal, distance_vertical);
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
	increment_y = CUBE_SIZE;
	if (ft_is_facing_down(map->prj->view_angle) == 0)
		increment_y *= -1;
	increment_x = ft_tangent_sign_per_quadrant(map->prj->view_angle,
			CUBE_SIZE / tan(map->prj->view_angle * (PI / 180)));
	y = floor(map->prj->rc_horizontal->y / CUBE_SIZE);
	x = floor(map->prj->rc_horizontal->x / CUBE_SIZE);
	printf("height: %d, width: %d\n", map->height, map->width);
	while (y >= 0 && x >= 0 && y < map->height && x < map->width)
	{
		printf("y: %d, x: %d\n", y, x);
		if (map->map_content[y][x] == '1')
			break ;
		else
		{
			map->prj->rc_horizontal->y += increment_y;
			map->prj->rc_horizontal->x += increment_x;
			y = floor(map->prj->rc_horizontal->y / CUBE_SIZE);
			x = floor(map->prj->rc_horizontal->x / CUBE_SIZE);
		}
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
	increment_x = CUBE_SIZE;
	if (ft_is_facing_right(map->prj->view_angle) == 0)
		increment_x *= -1;
	increment_y = ft_tangent_sign_per_quadrant(map->prj->view_angle,
			CUBE_SIZE * tan(map->prj->view_angle * (PI / 180)));
	y = floor(map->prj->rc_vertical->y / CUBE_SIZE);
	x = floor(map->prj->rc_vertical->x / CUBE_SIZE);
	while (y >= 0 && x >= 0 && y < map->height && x < map->width)
	{
		printf("y: %d, x: %d\n", y, x);
		if (map->map_content[y][x] == '1')
			break ;
		else
		{
			map->prj->rc_vertical->y += increment_y;
			map->prj->rc_vertical->x += increment_x;
			y = floor(map->prj->rc_vertical->y / CUBE_SIZE);
			x = floor(map->prj->rc_vertical->x / CUBE_SIZE);
		}
	}
}

/*ft_get_ray_angle will calculate and set map->prj->Po
 * with the viewing angle for the column to raycast*/

void	ft_get_ray_angle(t_map *map)
{
	map->prj->view_angle = ft_set_viewing_angle(map->prj->player_orientation)
		- (map->column * map->prj->angle_btw_rays) + (FIELD_OF_VIEW / 2);
	if (map->prj->view_angle < 0)
		map->prj->view_angle += 360;
	if (map->prj->view_angle > 360)
		map->prj->view_angle -= 360;
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
		ft_free_raycast_data(map);
		map->column++;
	}
	mlx_put_image_to_window(map->view->mlx, map->view->mlx_win,
		map->view->plane_data->img, 0, 0);
}
