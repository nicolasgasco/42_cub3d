/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_desc_file_validation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/06/09 13:14:58 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void ft_render_view(t_view *view, t_rdata *rdata, t_map *map)
{
	view->width = WIN_WIDTH;
	view->height = WIN_HEIGHT;
	view->title = ft_strdup(GAME_TITLE);
	view->mlx = mlx_init();
	view->mlx_win = mlx_new_window(view->mlx, view->width,
								   view->height, view->title);
	view->plane_data = malloc(sizeof(t_data));
	ft_memset(view->plane_data, 0, sizeof(t_data)); 
	ft_view_events(view);

	ft_render_texture(view, &rdata->textures[NO_TEXTURE_INDEX], 0, 0);
	// ft_render_texture(view, &rdata->textures[NO_TEXTURE_INDEX], TEXTURE_SIZE * 1, 0);
	// ft_render_texture(view, &rdata->textures[NO_TEXTURE_INDEX], TEXTURE_SIZE * 2, 0);
	// ft_render_texture(view, &rdata->textures[NO_TEXTURE_INDEX], TEXTURE_SIZE * 3, 0);
	// ft_render_texture(view, &rdata->textures[NO_TEXTURE_INDEX], TEXTURE_SIZE * 4, 0);

	// ft_render_texture(view, &rdata->textures[SO_TEXTURE_INDEX], TEXTURE_SIZE * 5, 0);
	// ft_render_texture(view, &rdata->textures[SO_TEXTURE_INDEX], TEXTURE_SIZE * 6, 0);
	// ft_render_texture(view, &rdata->textures[SO_TEXTURE_INDEX], TEXTURE_SIZE * 7, 0);
	// ft_render_texture(view, &rdata->textures[SO_TEXTURE_INDEX], TEXTURE_SIZE * 8, 0);
	// ft_render_texture(view, &rdata->textures[SO_TEXTURE_INDEX], TEXTURE_SIZE * 9, 0);

	// ft_render_texture(view, &rdata->textures[WE_TEXTURE_INDEX], TEXTURE_SIZE * 0, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[WE_TEXTURE_INDEX], TEXTURE_SIZE * 1, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[WE_TEXTURE_INDEX], TEXTURE_SIZE * 2, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[WE_TEXTURE_INDEX], TEXTURE_SIZE * 3, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[WE_TEXTURE_INDEX], TEXTURE_SIZE * 4, TEXTURE_SIZE * 1);

	// ft_render_texture(view, &rdata->textures[EA_TEXTURE_INDEX], TEXTURE_SIZE * 5, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[EA_TEXTURE_INDEX], TEXTURE_SIZE * 6, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[EA_TEXTURE_INDEX], TEXTURE_SIZE * 7, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[EA_TEXTURE_INDEX], TEXTURE_SIZE * 8, TEXTURE_SIZE * 1);
	// ft_render_texture(view, &rdata->textures[EA_TEXTURE_INDEX], TEXTURE_SIZE * 9, TEXTURE_SIZE * 1);

	ft_render_whole_scene(view, map);
	
	mlx_loop(view->mlx);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_view_events(t_view *view)
{
	mlx_key_hook(view->mlx_win, ft_keyboard_events, view);
	mlx_hook(view->mlx_win, ON_DESTROY, 0, ft_close_window, view);
}

int ft_close_window(t_view *view)
{
	mlx_destroy_window(view->mlx, view->mlx_win);
	free(view->title);
	free(view->plane_data);
	exit(0);
}

int ft_keyboard_events(int key, t_view *view)
{
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(view);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX) || (key == W_KEY_MAC || key == UP_ARR_MAC))
	{
		printf("Arrow up or W\n");
	}
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX) || (key == A_KEY_MAC || key == LEFT_ARR_MAC))
	{
		printf("Arrow left or a\n");
	}
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX) || (key == S_KEY_MAC || key == DOWN_ARR_MAC))
	{
		printf("Arrow down or S\n");
	}
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX) || (key == D_KEY_MAC || key == RIGHT_ARR_MAC))
	{
		printf("Arrow right or D\n");
	}
	return (1);
}
