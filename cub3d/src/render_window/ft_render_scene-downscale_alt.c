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

	if (map->slc->height < 75)
		printf("\x1b[33mHeight is %d\x1b[0m\n", map->slc->height); // TBD - Only for debug
	dividers = (int *)malloc(sizeof(int) * 50);
	int height = TEXTURE_SIZE;
	int i = 0;
	while (1)
	{
		if ((height - map->slc->height) <= 1)
		{
			dividers[i] = 0;
			break;
		}
		dividers[i] = TEXTURE_SIZE / (height - map->slc->height) + 1;
		if (map->slc->height < 75)
			printf("Divider is %d\n", dividers[i]);
		height -= TEXTURE_SIZE / dividers[i];
		if (map->slc->height < 75)
			printf("Height is %d\n", height);
		i++;
	}
	ft_downscaled_texture_loop(map, dividers);
	free(dividers);
}

void	ft_downscaled_texture_loop(t_map *map, int *dividers)
{
	int	j;
	int x;
	int	i;
	int	modulo_not_zero;

	x = 0;
	i = 0;
	while (i < map->slc->height && map->y < PROJ_PLANE_HEIGHT)
	{
		modulo_not_zero = 1;
		j = 0;
		int offset = 0;
		while (dividers[j] != 0)
		{
			if ((x + offset) % dividers[j] == 0)
				modulo_not_zero = 0;
			if (offset == 0)
				offset++;
			else
				offset--;
			j++;
		}
		if (modulo_not_zero == 1)
		{
			my_mlx_pixel_put(map->view->plane_data, map->slc->column, map->y,
				map->rdata->textures[NO_TEXTURE_INDEX].texture_columns[x][0]);
			i += 1;
			map->y += 1;
		}
		x++;
	}
	if (map->slc->height == 71)
		printf("X is %d\n", x);
}

