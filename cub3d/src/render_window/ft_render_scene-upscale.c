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

void	ft_render_upscaled_texture(t_map *map)
{
	int	divider;

	if ((map->slc->height / TEXTURE_SIZE) > 1)
	{
		divider = (map->slc->height / TEXTURE_SIZE) + 1;
		printf("Multiplier\n");
		ft_multiplied_texture_loop(map, divider);
	}
	else
	{
		divider = TEXTURE_SIZE / (map->slc->height - TEXTURE_SIZE);
		if (divider == 1)
			divider++;
		ft_upscaled_texture_loop(map, divider);
	}
}

void	ft_upscaled_texture_loop(t_map *map, int divider)
{
	int	x;
	int	i;
	int	limit;

	x = 0;
	i = 0;
	limit = map->slc->height / 4;
	while (i < limit)
		ft_upscaled_texture_loop_pixel_put(map, divider, &i, &x);
	x = (TEXTURE_SIZE / 4) - 1;
	limit = map->slc->height / 2;
	while (i < limit)
		ft_upscaled_texture_loop_pixel_put(map, divider, &i, &x);
	x = (TEXTURE_SIZE / 2) - 1;
	limit = map->slc->height / 4 * 3;
	while (i < limit)
		ft_upscaled_texture_loop_pixel_put(map, divider, &i, &x);
	x = (TEXTURE_SIZE / 4) * 3 - 1;
	limit = map->slc->height;
	while (i < limit)
		ft_upscaled_texture_loop_pixel_put(map, divider, &i, &x);
}

void	ft_upscaled_texture_loop_pixel_put(t_map *map, int divider,
	int *i, int *x)
{
	my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
		map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
	if (*i % divider != 0)
		*x += 1;
	map->y += 1;
	*i += 1;
}
