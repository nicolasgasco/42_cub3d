/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/19 13:35:50 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_move_forward(t_map *map)
{
	double	radians;
	int		v_increase;
	int		l_increase;

	radians = map->prj->view_angle * (M_PI / 180);
	v_increase = V_MOVEMENT_INCREMENT * sin(radians);
	l_increase = V_MOVEMENT_INCREMENT * cos(radians);
	map->prj->player->y -= v_increase;
	map->prj->player->x += l_increase;
}

void	ft_move_back(t_map *map)
{
	double	radians;
	int		v_increase;
	int		l_increase;

	radians = map->prj->view_angle * (M_PI / 180);
	v_increase = V_MOVEMENT_INCREMENT * sin(radians);
	l_increase = V_MOVEMENT_INCREMENT * cos(radians);
	map->prj->player->y += v_increase;
	map->prj->player->x -= l_increase;
}

void	ft_rotate_leftwards(t_map *map)
{
	int	new_angle;

	new_angle = (map->prj->view_angle + L_MOVEMENT_INCREMENT) % 360;
	map->prj->view_angle = new_angle;
}

void	ft_rotate_rightwards(t_map *map)
{
	int	new_angle;
	int	current_angle;

	current_angle = map->prj->view_angle;
	if (current_angle == 0)
		current_angle = 360;
	else if (current_angle < 0)
		current_angle = 360 - abs(current_angle);
	new_angle = current_angle - L_MOVEMENT_INCREMENT;
	map->prj->view_angle = new_angle;
}

int	ft_angle_to_degrees(int angle)
{
	return ((angle * FIELD_OF_VIEW) / WIN_WIDTH);
}
