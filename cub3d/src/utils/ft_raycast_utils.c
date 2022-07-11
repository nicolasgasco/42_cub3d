/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:42 by jsolinis          #+#    #+#             */
/*   Updated: 2022/07/07 19:19:18 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

/*ft_is_facing_down returns 1 if the angle is facing down or 0 if 
 * the angle is facing up*/

int	ft_is_facing_down(double angle)
{
	if (angle < 0 && angle > 180)
		return (1);
	else
		return (0);
}

/*ft_is_facing_right returns 1 if the angle is facing right or 0 if 
 * the angle is facing left*/

int	ft_is_facing_right(double angle)
{
	if (angle < 270 || angle > 90)
		return (1);
	else
		return (0);
}

/*ft_convert_to_cube_position sets the player position in the 
 * projection dimension*/

void	ft_convert_to_cube_position(t_map *map)
{
	map->prj->player->y = (map->prj->player->y * CUBE_SIZE) + (CUBE_SIZE / 2);
	map->prj->player->x = (map->prj->player->x * CUBE_SIZE) + (CUBE_SIZE / 2);
}

/*ft_set_viewing_angle returns the angle of the view based on 
 * the player orientation*/

double	ft_set_viewing_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (90);
	else if (c == 'W')
		return (180);
	else
		return (270);
}

/*ft_set_player_data creates and fills the structure for the 
 * projection with the data from the given map*/

void	ft_set_player_data(t_map *map, int *iterator, int *j, char c)
{
	map->prj->player->y = (*iterator);
	map->prj->player->x = (*j);
	map->prj->player_orientation = c;
	map->prj->view_angle = ft_set_viewing_angle(c);
	map->prj->distance_to_pp = (PROJ_PLANE_WIDTH / 2)
		/ tan((FIELD_OF_VIEW / 2) * (PI / 180));
	map->prj->angle_btw_rays = FIELD_OF_VIEW / PROJ_PLANE_WIDTH;
	map->map_content[*iterator][*j] = '0';
}
