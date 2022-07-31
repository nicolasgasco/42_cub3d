/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:27 by jsolinis          #+#    #+#             */
/*   Updated: 2022/07/24 13:05:01 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/* ft_transform_angle converts the angle value to the rendered plane angle
 * based on projection plane width and the field of view */

int	ft_transform_angle(int angle)
{
	if (angle == 0)
		return (0);
	return ((angle * WIN_WIDTH) / FIELD_OF_VIEW);
}

/* ft_increment adds the increment vector to the current position */

t_vector	ft_increment(t_vector position, t_vector increment)
{
	t_vector	ret;

	ret.x = position.x + increment.x;
	ret.y = position.y + increment.y;
	return (ret);
}

/* ft_hit verifies if the new position is within the map and if there is 
 * a wall in that position */

int	ft_hit(t_map *map, t_vector position, int angle)
{
	int	y;
	int	x;

	if (position.y < 0 || position.x < 0 || (position.y / TEXTURE_SIZE) >= (map->height - 1)
		|| (position.x / TEXTURE_SIZE) >= map->width)
		return (1);
	if (ft_is_facing_down(angle) == 0)
		y = ceil(position.y) / TEXTURE_SIZE;
	else
		y = floor(position.y) / TEXTURE_SIZE;
	if (ft_is_facing_right(angle))
		x = ceil(position.x) / TEXTURE_SIZE;
	else
		x = floor(position.x) / TEXTURE_SIZE;
	if (map->map_content[y][x] == '1')
		return (1);
	return (0);
}
