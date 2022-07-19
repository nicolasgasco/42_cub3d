/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene-multiply.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/16 21:19:24 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_multiplied_texture_loop(t_map *map, int multiplier)
{
	int	x;
	int	i;
	int	*dividers;

	x = 0;
	i = 0;
	dividers = ft_populate_dividers_multiplier(multiplier, map->slc->height);
	while (i < map->slc->height && map->y < (PROJ_PLANE_HEIGHT - 1))
	{
		ft_render_multiplied_pixels(map, dividers, &x, &i);
		ft_render_remaining_multiplied_pixels(map, dividers, &x, &i);
		if (x < (TEXTURE_SIZE - 2))
			x += 1;
	}
	free(dividers);
}

int	*ft_populate_dividers_multiplier(int multiplier, int height)
{
	int	i;
	int	already_rendered;
	int	*dividers;

	dividers = (int *)malloc(sizeof(int) * 50);
	ft_memset(dividers, 0, sizeof(dividers));
	already_rendered = (height - TEXTURE_SIZE * multiplier);
	dividers[0] = multiplier;
	i = 1;
	while (1)
	{
		if (already_rendered != 0)
			dividers[i] = TEXTURE_SIZE / (already_rendered) + 1;
		if (dividers[i] <= 0 || dividers[i] >= TEXTURE_SIZE)
		{
			dividers[i] = 15;
			dividers[i + 1] = 0;
			break ;
		}
		already_rendered -= TEXTURE_SIZE / dividers[i];
		i++;
	}
	return (dividers);
}

void	ft_render_multiplied_pixels(t_map *map, int *dividers,
			int *x, int *i)
{
	int	j;

	j = 0;
	while (j < dividers[0] && map->y < PROJ_PLANE_HEIGHT)
	{
		if (map->y < PROJ_PLANE_HEIGHT) // TBD
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
		map->y += 1;
		*i += 1;
		j++;
	}
}

void	ft_render_remaining_multiplied_pixels(t_map *map, int *dividers,
			int *x, int *i)
{
	int	j;

	j = 1;
	while (dividers[j] != 0)
	{
		if ((((*x + 1) % dividers[j]) == 0))
		{
			if (map->y < PROJ_PLANE_HEIGHT) // TBD
				my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
					map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[*x][0]);
			map->y += 1;
			*i += 1;
		}
		j++;
	}
}
