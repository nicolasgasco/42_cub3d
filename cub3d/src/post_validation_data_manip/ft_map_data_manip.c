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

void ft_post_validation_data_manip(t_map *map, t_rdata *rdata)
{
	rdata->c_col_int = ft_rgb_str_to_int(map->c_color);
	ft_write_debug_msg_int("Ceiling color is ", rdata->c_col_int);
	rdata->f_col_int = ft_rgb_str_to_int(map->f_color);
	ft_write_debug_msg_int("Floor color is ", rdata->f_col_int);
	rdata->textures = (t_tdata *)malloc(sizeof(t_tdata) * NUM_TEXTURES);
	rdata->NO_TEXTURE = ft_texture_file_to_columns(map->no_path);
	rdata->EA_TEXTURE = ft_texture_file_to_columns(map->ea_path);
	rdata->SO_TEXTURE = ft_texture_file_to_columns(map->so_path);
	rdata->WE_TEXTURE = ft_texture_file_to_columns(map->we_path);
}
