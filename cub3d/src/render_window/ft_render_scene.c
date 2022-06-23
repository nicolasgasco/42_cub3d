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

void	ft_render_game_scene(t_view *view, t_map *map)
{
	if (view->plane_data->img)
		mlx_destroy_image(view->mlx, view->plane_data->img);
	view->plane_data->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_raycasting_calculation(map);
}

void	ft_render_raycasting_column(t_map *map)
{
	t_data	*plane;

	plane = map->view->plane_data;
	plane->addr = mlx_get_data_addr(plane->img, &plane->bits_per_pixel,
			&plane->line_length, &plane->endian);
	printf("\x1b[33mColumn is %d, Height is %d\x1b[0m\n", map->slc->column, map->slc->height); // TBD - Only for debug
	if (map->slc->height < 0 || map->slc->height > PROJ_PLANE_HEIGHT) // TBD - Only for debug
		map->slc->height = 0; // TBD - Only for debug
	map->y = 0;
	ft_render_ceiling(map, &map->y);
	ft_render_scaled_texture(map); // Commented if you want to see raycasting without textures
	// ft_render_solid_color(map, &y); // Uncommented if you want to see raycasting without textures
	ft_render_floor(map, &map->y);
}

void	ft_render_ceiling(t_map *map, int *y)
{
	int	offset;

	offset = (PROJ_PLANE_HEIGHT - map->slc->height) / 2;
	while (*y < offset)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column,
			*y, map->rdata->c_col_int);
		*y += 1;
	}
	if (*y == 0) // TBD - Only for debug
		*y = offset; // TBD - Only for debug
}

void	ft_render_floor(t_map *map, int *y)
{
	while (*y < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column,
			*y, map->rdata->f_col_int);
		*y += 1;
	}
}

/* Use this if you want to see raycasting without textures */
void	ft_render_solid_color(t_map *map, int *y)
{
	int	i;

	i = 0;
	while (i < map->slc->height && *y < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(map->view->plane_data, map->slc->column, *y, 0x22E100);
		i += 1;
		*y += 1;
	}
}
