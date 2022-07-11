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

void	ft_render_downscaled_texture(t_map *map)
{
	int	*dividers;
	int	i;
	int	height;

	if (map->slc->height < 75)
		printf("\x1b[33mHeight is %d\x1b[0m\n", map->slc->height); // TBD - Only for debug
	dividers = (int *)malloc(sizeof(int) * 10);
	height = TEXTURE_SIZE;
	i = 0;
	while (1)
	{
		if ((height - map->slc->height) <= 1)
		{
			dividers[i] = 0;
			break ;
		}
		dividers[i] = TEXTURE_SIZE / (height - map->slc->height) + 1;
		height -= TEXTURE_SIZE / dividers[i];
		i++;
	}
	ft_downscaled_texture_loop(map, dividers);
	free(dividers);
}

void	ft_downscaled_texture_loop(t_map *map, int *dividers)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (i < map->slc->height && map->y < PROJ_PLANE_HEIGHT)
	{
		if (module_not_zero_for_all(dividers, x) == 1)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i += 1;
			map->y += 1;
		}
		x++;
	}
}

int	module_not_zero_for_all(int *dividers, int x)
{
	int	modulo_not_zero;
	int	offset;
	int	j;

	modulo_not_zero = 1;
	j = 0;
	offset = 0;
	while (dividers[j] != 0)
	{
		if ((x + offset) % dividers[j] == 0)
			modulo_not_zero = 0;
		if (offset == 0)
			offset = 1;
		else
			offset = 0;
		j++;
	}
	return (modulo_not_zero);
}
