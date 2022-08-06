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

void	ft_view_events(t_map *map)
{
	mlx_hook(map->view->mlx_win, ON_KEY_DOWN, 1L<<0, ft_keyboard_events, map);
	mlx_mouse_hook(map->view->mlx_win, ft_mouse_events, map);
	mlx_hook(map->view->mlx_win, ON_DESTROY, 0, ft_close_window, map);
}

int	ft_keyboard_events(int key, t_map *map)
{
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(map);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX)
		|| (key == W_KEY_MAC || key == UP_ARR_MAC))
		ft_move_forward(map, V_MOVEMENT_INCREMENT);
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX)
		|| (key == A_KEY_MAC || key == LEFT_ARR_MAC))
		ft_rotate_leftwards(map, L_MOVEMENT_INCREMENT);
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX)
		|| (key == S_KEY_MAC || key == DOWN_ARR_MAC))
		ft_move_back(map, V_MOVEMENT_INCREMENT);
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX)
		|| (key == D_KEY_MAC || key == RIGHT_ARR_MAC))
		ft_rotate_rightwards(map, L_MOVEMENT_INCREMENT);
	ft_render_game_scene(map);
	return (1);
}

int	ft_mouse_events(int button, int x, int y, t_map *map)
{
	int	win_half;
	int	degrees;

	win_half = WIN_WIDTH / 2;
	if (button != LEFT_CLICK && y)
		return (1);
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
	ft_move_forward(map, V_MOVEMENT_INCREMENT);
	ft_render_game_scene(map);
	return (0);
}

int	ft_close_window(t_map *map)
{
	mlx_destroy_window(map->view->mlx, map->view->mlx_win);
	ft_free_allocated_map_data(map);
	exit (0);
}
