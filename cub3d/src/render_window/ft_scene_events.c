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
	mlx_hook(map->view->mlx_win, ON_KEY_DOWN, 0, ft_keyboard_events, map);
	mlx_hook(map->view->mlx_win, ON_DESTROY, 0, ft_close_window, map);
}

int	ft_keyboard_events(int key, t_map *map)
{
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(map);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX)
		|| (key == W_KEY_MAC || key == UP_ARR_MAC))
		ft_move_forward(map);
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX)
		|| (key == A_KEY_MAC || key == LEFT_ARR_MAC))
		ft_rotate_leftwards(map);
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX)
		|| (key == S_KEY_MAC || key == DOWN_ARR_MAC))
		ft_move_back(map);
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX)
		|| (key == D_KEY_MAC || key == RIGHT_ARR_MAC))
		ft_rotate_rightwards(map);
	ft_render_game_scene(map);
	return (1);
}

int	ft_close_window(t_map *map)
{
	mlx_destroy_window(map->view->mlx, map->view->mlx_win);
	ft_free_allocated_map_data(map);
	exit(0);
}
