/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:27 by jsolinis          #+#    #+#             */
/*   Updated: 2022/07/11 13:41:41 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <math.h>

/*ft_tangent_sign_per_qadrant will set the correct signed result
 * the tangent of the angle should have based on the quadrant*/

double	ft_tangent_sign_per_quadrant(double angle, double tangent)
{
	if (angle > 90 && angle < 180 && tangent > 0)
		return (tangent * -1);
	else if (angle > 0 && angle < 90 && tangent < 0)
		return (tangent * -1);
	else if (angle > 180 && angle < 270 && tangent < 0)
		return (tangent * -1);
	else if (angle > 270 && angle < 360 && tangent > 0)
		return (tangent * -1);
	else
		return (tangent);
}

/*ft_set_coords_angle_direction_horizontal sets the starting values 
 * for rc->horizontal y & x based on the angle orientation*/

void	ft_set_coords_angle_direction_horizontal(t_map *map)
{
	t_vector	*horizontal;
	double		tangent;

	horizontal = malloc(sizeof(t_vector));
	ft_memset(horizontal, 0, sizeof(t_vector));
	map->prj->rc_horizontal = horizontal;
	map->prj->rc_horizontal->y = floor(map->prj->player->y
			/ CUBE_SIZE) * CUBE_SIZE;
	if (ft_is_facing_down(map->prj->view_angle))
		map->prj->rc_horizontal->y += CUBE_SIZE;
	else
		map->prj->rc_horizontal->y -= 1;
	tangent = ft_tangent_sign_per_quadrant(map->prj->view_angle,
			tan(map->prj->view_angle * (PI / 180)));
	map->prj->rc_horizontal->x = map->prj->player->x
		+ (map->prj->rc_horizontal->y - map->prj->player->y)
		/ tangent;
}

/*ft_set_coords_angle_direction_vertical sets the starting values 
 * for rc->vertical y & x based on the angle orientation*/

void	ft_set_coords_angle_direction_vertical(t_map *map)
{
	t_vector	*vertical;
	double		tangent;

	vertical = malloc(sizeof(t_vector));
	ft_memset(vertical, 0, sizeof(t_vector));
	map->prj->rc_vertical = vertical;
	map->prj->rc_vertical->x = floor(map->prj->player->x
			/ CUBE_SIZE) * CUBE_SIZE;
	if (ft_is_facing_right(map->prj->view_angle))
		map->prj->rc_vertical->x += CUBE_SIZE;
	else
		map->prj->rc_vertical->x -= 1;
	tangent = ft_tangent_sign_per_quadrant(map->prj->view_angle,
			tan(map->prj->view_angle * (PI / 180)));
	map->prj->rc_vertical->y = map->prj->player->y
		+ (map->prj->rc_vertical->x - map->prj->player->x)
		* tangent;
}
