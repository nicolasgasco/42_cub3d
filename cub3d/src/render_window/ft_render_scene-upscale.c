/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene-upscale.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/16 21:19:02 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_render_upscaled_texture(t_map *map)
{
	int	divider;

	if ((map->slc->height / TEXTURE_SIZE) > 1)
	{
		divider = (map->slc->height / TEXTURE_SIZE);
		ft_multiplied_texture_loop(map, divider);
	}
	else
	{
		divider = TEXTURE_SIZE / (map->slc->height - TEXTURE_SIZE);
		divider += 1;
		if ((map->slc->height - (TEXTURE_SIZE + TEXTURE_SIZE / 2)) < 0)
		{
			divider = TEXTURE_SIZE / (map->slc->height - TEXTURE_SIZE);
		}
		ft_upscaled_texture_loop(map, divider);
	}
}

void	ft_upscaled_texture_loop(t_map *map, int divider)
{
	int	x;
	int	i;
	int	*dividers;

	x = 0;
	i = 0;
	dividers = ft_populate_dividers_upscale(divider, map->slc->height);
	while (i < map->slc->height)
	{
		ft_render_standard_pixels(map, &x, &i);
		ft_render_upscaled_pixels(map, dividers, &x, &i);
		if (x < (TEXTURE_SIZE - 1)) // TBD - if possible
			x += 1;
	}
}

int	*ft_populate_dividers_upscale(int divider, int height)
{
	int	i;
	int	*dividers;
	int	already_rendered;

	dividers = (int *)malloc(sizeof(int) * 50);
	dividers[0] = divider;
	already_rendered = TEXTURE_SIZE / divider;
	i = 1;
	while (1)
	{
		if (height - (TEXTURE_SIZE + already_rendered) != 0)
			dividers[i] = TEXTURE_SIZE / (height
				- (TEXTURE_SIZE + already_rendered)) + 1;
		if (dividers[i] <= 1)
		{
			dividers[i] = TEXTURE_SIZE / 3;
			dividers[i + 1] = 0;
			break ;
		}
		i++;
		divider++;
		already_rendered += TEXTURE_SIZE / divider;
	}
	return (dividers);
}

void	ft_render_standard_pixels(t_map *map, int *x, int *i)
{
	my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
		map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
	map->y += 1;
	*i += 1;
}

void	ft_render_upscaled_pixels(t_map *map, int *dividers,
			int *x, int *i)
{
	int	j;

	j = 0;
	while (dividers[j] != 0)
	{
		if (((*x + 1) % dividers[j]) == 0)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
			map->y += 1;
			*i += 1;
		}
		j++;
	}
}
