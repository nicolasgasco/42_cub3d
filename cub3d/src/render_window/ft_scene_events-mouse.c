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

int	ft_mouse_events(int button, int x, int y, t_map *map)
{
	if (button != LEFT_CLICK && y)
		return (1);
	ft_mouse_rotation(x, map);
	ft_mouse_v_movement(y, map);
	ft_render_game_scene(map);
	return (0);
}

void	ft_mouse_rotation(int x, t_map *map)
{
	int	win_half;
	int	degrees;

	win_half = WIN_WIDTH / 2;
	if (x >= win_half)
	{
		x -= win_half;
		degrees = x * (FIELD_OF_VIEW / 2) / win_half;
		if (degrees > L_MOVEMENT_INCREMENT)
			degrees = L_MOVEMENT_INCREMENT;
		ft_rotate_rightwards(map, degrees);
	}
	else
	{
		x = win_half - x;
		degrees = x * (FIELD_OF_VIEW / 2) / win_half;
		if (degrees > L_MOVEMENT_INCREMENT)
			degrees = L_MOVEMENT_INCREMENT;
		ft_rotate_leftwards(map, degrees);
	}
}

void	ft_mouse_v_movement(int y, t_map *map)
{
	int	win_half;

	win_half = WIN_WIDTH / 2;
	if (y <= win_half)
		ft_move_forward(map, V_MOVEMENT_INCREMENT);
	else
		ft_move_back(map, V_MOVEMENT_INCREMENT);
}
