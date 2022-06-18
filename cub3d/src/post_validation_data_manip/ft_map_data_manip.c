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

void	ft_post_validation_data_manip(t_map *map, t_rdata *rdata)
{
	rdata->c_col_int = ft_rgb_str_to_int(map->c_color);
	ft_write_debug_msg_int("Ceiling color is ", rdata->c_col_int);
	rdata->f_col_int = ft_rgb_str_to_int(map->f_color);
	ft_write_debug_msg_int("Floor color is ", rdata->f_col_int);
	rdata->textures = (t_tdata *)malloc(sizeof(t_tdata) * NUM_TEXTURES);
	rdata->textures[NO_TEXTURE_INDEX] = ft_texture_file_to_columns(map->no_path);
	rdata->textures[EA_TEXTURE_INDEX] = ft_texture_file_to_columns(map->ea_path);
	rdata->textures[SO_TEXTURE_INDEX] = ft_texture_file_to_columns(map->so_path);
	rdata->textures[WE_TEXTURE_INDEX] = ft_texture_file_to_columns(map->we_path);
}

t_tdata	ft_texture_file_to_columns(char *texture_path)
{
	t_tdata	*texture;
	int		fd;
	char	*line;

	fd = open(texture_path, O_RDONLY);
	if (fd == -1)
		ft_open_file_error();
	texture = (t_tdata *)malloc(sizeof(t_tdata));
	ft_memset(texture, 0, sizeof(t_tdata));
	line = NULL;
	ft_readline_asset_sizes(fd, line, texture);
	ft_readline_color_codes(fd, line, texture);
	ft_readline_char_map(fd, line, texture);
	return (*texture);
}

void	ft_free_allocated_render_data(t_rdata *rdata)
{
	// Free s_cinfo
	free(rdata);
}