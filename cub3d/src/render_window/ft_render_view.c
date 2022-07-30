/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_view.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/19 12:25:54 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_render_view(t_map *map)
{

	map->view->width = WIN_WIDTH;
	map->view->height = WIN_HEIGHT;
	map->view->title = ft_strdup(GAME_TITLE);
	map->view->mlx = mlx_init();
	map->view->mlx_win = mlx_new_window(map->view->mlx, map->view->width,
			map->view->height, map->view->title);
	map->view->plane_data = malloc(sizeof(t_data));
	ft_memset(map->view->plane_data, 0, sizeof(t_data));
	ft_view_events(map);
	ft_render_game_scene(map);
	mlx_loop(map->view->mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_view_events(t_map *map)
{
	mlx_key_hook(map->view->mlx_win, ft_keyboard_events, map->view);
	mlx_hook(map->view->mlx_win, ON_DESTROY, 0, ft_close_window, map->view);
}

int	ft_close_window(t_map *map)
{
	mlx_destroy_window(map->view->mlx, map->view->mlx_win);
	free(map->view->title);
	free(map->view->plane_data);
	exit(0);
}

int	ft_keyboard_events(int key, t_map *map)
{
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(map);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX)
		|| (key == W_KEY_MAC || key == UP_ARR_MAC))
	{
		printf("Arrow up or W\n");
	}
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX)
		|| (key == A_KEY_MAC || key == LEFT_ARR_MAC))
	{
		printf("Arrow left or a\n");
	}
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX)
		|| (key == S_KEY_MAC || key == DOWN_ARR_MAC))
	{
		printf("Arrow down or S\n");
	}
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX)
		|| (key == D_KEY_MAC || key == RIGHT_ARR_MAC))
	{
		printf("Arrow right or D\n");
	}
	return (1);
}
