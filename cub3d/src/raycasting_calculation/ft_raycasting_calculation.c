/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_calculation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:56:57 by jsolinis          #+#    #+#             */
/*   Updated: 2022/07/19 13:33:33 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <math.h>

/*ft_horizontal_intersection will find the hit(s) with the
 * horizontal axis of the map until there is a wall*/

double	ft_horizontal_intersection(t_map *map, int current_angle)
{
	t_vector	intersection;
	t_vector	increment;

	intersection.y = floor(map->prj->player->y / CUBE_SIZE) * CUBE_SIZE;
	if (ft_is_facing_down(current_angle) == 0)
		intersection.y -= 1;
	else
		intersection.y += CUBE_SIZE;
	intersection.x = map->prj->player->x
		+ (map->prj->player->y - intersection.y) / ft_tangent(current_angle);
	increment = ft_horizontal_increment(current_angle);
	while (ft_hit(map, intersection, current_angle) == 0)
		intersection = ft_increment(intersection, increment);
	if (intersection.y < 0 || intersection.x < 0 || intersection.y / CUBE_SIZE
		> map->height || intersection.x / CUBE_SIZE > map->width)
		return (2147483647);
	return (fabs(fabs(map->prj->player->y - intersection.y) / ft_sine(current_angle)));
}

/*ft_vertical_intersection will find the hit(s) with the
 * vertical axis of the map until there is a wall*/

double	ft_vertical_intersection(t_map *map, int current_angle)
{
	t_vector	intersection;
	t_vector	increment;

	intersection.x = floor(map->prj->player->x / CUBE_SIZE) * CUBE_SIZE;
	if (ft_is_facing_right(current_angle) == 0)
		intersection.x -= 1;
	else
		intersection.x += CUBE_SIZE;
	intersection.y = map->prj->player->y
		+ (map->prj->player->x - intersection.x) * ft_tangent(current_angle);
	increment = ft_vertical_increment(current_angle);
	while (ft_hit(map, intersection, current_angle) == 0)
		intersection = ft_increment(intersection, increment);
	if (intersection.y < 0 || intersection.x < 0 || intersection.y / CUBE_SIZE
		> map->height || intersection.x / CUBE_SIZE > map->width)
		return (2147483647);
	return (fabs(fabs(map->prj->player->x - intersection.x) / ft_cosine(current_angle)));
}

/*ft_calculate_distance will calculate the distances from 
 * the player to the horizontal & vertical intersections.*/

double	ft_calculate_distance(t_map *map)
{
	int		current_angle;
	double	distance_horizontal;
	double	distance_vertical;

	current_angle = map->prj->view_angle + map->slc->angle;
	if (current_angle < 0)
		current_angle += ft_transform_angle(360);
	if (current_angle >= ft_transform_angle(360))
		current_angle -= ft_transform_angle(360);
	distance_horizontal = ft_horizontal_intersection(map, current_angle); 
	distance_vertical = ft_vertical_intersection(map, current_angle);
	if (distance_horizontal < distance_vertical)
		return (distance_horizontal);
	else
		return (distance_vertical);
}

/*ft_raycasting_calculation initializes the loop to
 * calculate & render the rays or slices.*/

void	ft_raycasting_calculation(t_map *map)
{	
	t_slice	*slc;

	slc = malloc (sizeof(t_slice));
	ft_memset(slc, 0, sizeof(t_slice));
	map->slc = slc;
	ft_convert_to_cube_position(map);
	map->slc->angle = ft_transform_angle(30);
	while (map->slc->angle > (ft_transform_angle(30) * -1) 
			&& map->slc->column < PROJ_PLANE_WIDTH)
	{
		map->slc->distance_to_wall = ft_calculate_distance(map);
		map->slc->height = map->slc->distance_to_wall * ft_cosine(abs(map->slc->angle));
		map->slc->height = (((double)(CUBE_SIZE)) / map->slc->height) * map->prj->distance_to_pp;
		printf("The NEW calc height %d\n", map->slc->height);
		ft_render_raycasting_column(map);
		map->slc->column++;
		map->slc->angle--;
	}
	mlx_put_image_to_window(map->view->mlx, map->view->mlx_win,
		map->view->plane_data->img, 0, 0);
}
