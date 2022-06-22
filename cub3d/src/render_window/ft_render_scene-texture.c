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

void	ft_render_scaled_texture(t_map *map, int *y)
{
	if (map->slc->height <= 0) // TBD - Only for debug
		return ; // TBD - Only for debug
	if (map->slc->height > TEXTURE_SIZE)
	{
		printf("Texture must be upscaled\n"); // TBD - Only for debug
		ft_render_solid_color(map, y);
	}
	else if (map->slc->height < TEXTURE_SIZE)
	{
		printf("Texture must be downscaled\n"); // TBD - Only for debug
		ft_render_downscaled_texture(map, y);
	}
}

void	ft_render_downscaled_texture(t_map *map, int *y)
{
	int	divider;

	divider = TEXTURE_SIZE / (TEXTURE_SIZE - map->slc->height) + 1;
	ft_render_downscaled_first_half(map, y, divider);
	ft_render_downscaled_second_half(map, y, divider);
}

void	ft_render_downscaled_first_half(t_map *map, int *y, int divider)
{
	int	x;
	int	i;
	int	limit;

	x = 0;
	i = 0;
	limit = map->slc->height / 2;
	while (i < limit && *y < PROJ_PLANE_HEIGHT) // Second condition TBD
	{
		if (x % divider != 0)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, *y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i += 1;
			*y += 1;
		}
		x++;
	}
	x = (TEXTURE_SIZE / 4);
	limit = map->slc->height / 2;
	while (i < limit && *y < PROJ_PLANE_HEIGHT) // Second condition TBD
	{
		if (x % divider != 0)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, *y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i += 1;
			*y += 1;
		}
		x++;
	}
}

void	ft_render_downscaled_second_half(t_map *map, int *y, int divider)
{
	int	i;
	int	x;
	int	limit;

	i = map->slc->height - 1;
	x = TEXTURE_SIZE - 1;
	limit = map->slc->height / 4 * 3;
	while (i > limit)
	{
		if (x % divider != 0)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, *y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i -= 1;
			*y += 1;
		}
		x--;
	}
	x = TEXTURE_SIZE - (TEXTURE_SIZE / 4);
	limit = map->slc->height / 2;
	while (i >= limit)
	{
		if (x % divider != 0)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column,*y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i -= 1;
			*y += 1;
		}
		x--;
	}
}
