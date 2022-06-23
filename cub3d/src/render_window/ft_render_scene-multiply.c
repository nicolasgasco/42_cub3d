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

void	ft_render_multiply_first_half(t_map *map, int divider)
{
	int	x;
	int	i;
	int	limit;

	x = 0;
	i = 0;
	limit = map->slc->height / 4;
	while (i < limit)
		ft_render_multiply_first_half_pixel_put(map, divider, &x, &i);
	x = (TEXTURE_SIZE / 4);
	limit = map->slc->height / 2;
	while (i < limit)
		ft_render_multiply_first_half_pixel_put(map, divider, &x, &i);
}

void	ft_render_multiply_first_half_pixel_put(t_map *map, int divider,
	int *x, int *i)
{
	int	j;

	j = 0;
	while (j < divider)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
			map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
		*i += 1;
		map->y += 1;
		j++;
	}
	*x += 1;
}

void	ft_render_multiply_second_half(t_map *map, int divider)
{
	int	i;
	int	x;
	int	limit;

	i = map->slc->height - 1;
	x = TEXTURE_SIZE - 1;
	limit = map->slc->height / 4 * 3;
	while (i > limit)
		ft_render_multiply_second_half_pixel_put(map, divider, &i, &x);
	x = TEXTURE_SIZE - (TEXTURE_SIZE / 4);
	limit = map->slc->height / 2;
	while (i > limit)
		ft_render_multiply_second_half_pixel_put(map, divider, &i, &x);
}

void	ft_render_multiply_second_half_pixel_put(t_map *map, int divider,
	int *i, int *x)
{
	int	j;

	j = 0;
	while (j < divider)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
			map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
		*i -= 1;
		map->y += 1;
		j++;
	}
	*x -= 1;
}
