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

void	ft_render_scaled_texture(t_map *map)
{
	printf("map->slc->height is %d\n", map->slc->height);
	if (map->slc->height <= 0) // TBD - Only for debug
	{
		printf("Problem with height\n");
	}
	if (map->slc->height > TEXTURE_SIZE)
	{
		ft_render_upscaled_texture(map);
	}
	else if (map->slc->height < TEXTURE_SIZE)
	{
		printf("Texture must be downscaled\n"); // TBD - Only for debug
		ft_render_downscaled_texture(map);
	}
	else
		ft_render_actual_size_texture(map);
}

void	ft_render_actual_size_texture(t_map *map)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (i < map->slc->height)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
			map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
		map->y += 1;
		i += 1;
		if (x < (TEXTURE_SIZE - 1)) // TBD - if possible
			x += 1;
	}
}

/* Used for testing only. Renders one texture in 2d */
void	ft_render_texture(t_view *view, t_tdata *texture, int win_x, int win_y)
{
	t_data	img;
	int		y;
	int		x;

	img.img = mlx_new_image(view->mlx, texture->texture_w, texture->texture_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	y = 0;
	while (y < texture->texture_h)
	{
		x = 0;
		while (x < texture->texture_w)
		{
			my_mlx_pixel_put(&img, x, y, texture->texture_columns[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(view->mlx, view->mlx_win, img.img, win_x, win_y);
}
