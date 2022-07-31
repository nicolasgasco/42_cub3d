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
	if (map->slc->height <= PROJ_PLANE_HEIGHT)
		ft_render_texture_smaller_than_screen(map);
	else
		ft_render_texture_bigger_than_screen(map);
}

void	ft_render_texture_smaller_than_screen(t_map *map)
{
	float	divider;
	float	y;

	divider = (float)TEXTURE_SIZE / (float)map->slc->height;
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		ft_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
			map->rdata->textures[NO_TEXTURE_I].texture_columns[(int)y]
		[map->slc->wall_x]);
		map->y += 1;
		y += divider;
	}
}

void	ft_render_texture_bigger_than_screen(t_map *map)
{
	float	divider;
	float	y;
	float	texture_y;

	texture_y = (float)((map->slc->height - PROJ_PLANE_HEIGHT) / 2);
	y = (texture_y * (float)TEXTURE_SIZE) / (float)map->slc->height;
	divider = ((float)TEXTURE_SIZE - (y * 2.0f)) / (float)PROJ_PLANE_HEIGHT;
	while (map->y < PROJ_PLANE_HEIGHT)
	{
		ft_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
			map->rdata->textures[NO_TEXTURE_I].texture_columns[(int)y]
		[map->slc->wall_x]);
		map->y += 1;
		y += divider;
		texture_y += divider;
	}
}
