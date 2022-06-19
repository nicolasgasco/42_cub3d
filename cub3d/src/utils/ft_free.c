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

void	ft_free_allocated_map_data(t_map *map)
{
	if (map->map_content)
		free(map->map_content);
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->we_path)
		free(map->we_path);
	if (map->f_color)
		free(map->f_color);
	if (map->c_color)
		free(map->c_color);
	if (map->prj->player)
		free(map->prj->player);
	if (map->prj)
		free(map->prj);
}

void	ft_print_error_exit(t_map *map, char *msg, int err)
{
	int	i;

	ft_putendl_fd(msg, STDERR_FILENO);
	i = 0;
	while (i < map->height)
	{
		if (map->map_content[i])
			free(map->map_content[i]);
		i++;
	}
	ft_free_allocated_map_data(map);
	exit(err);
}

void	ft_free_raycast_data(t_map *map)
{
	if (map->prj->rc_horizontal)
		free(map->prj->rc_horizontal);
	if (map->prj->rc_vertical)
		free(map->prj->rc_vertical);
	if (map->prj->wall_to_render)
		free(map->prj->wall_to_render);
	if (map->slc)
		free(map->slc);
}
