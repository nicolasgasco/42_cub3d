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

void	ft_post_validation_data_manip(t_map *map, t_rdata *rdata)
{
	printf("Entering in post validation data manip\n");
	rdata->c_col_int = ft_rgb_str_to_int(map->c_color);
	printf("Ceiling color is %s\n", map->c_color);
	printf("Ceiling color is %x\n", rdata->c_col_int);
	rdata->f_col_int = ft_rgb_str_to_int(map->f_color);
	printf("Floor color is %s\n", map->f_color);
	printf("Floor color is %x\n", rdata->f_col_int);
}
