/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/19 13:35:50 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

int	ft_angle_to_degrees(int angle)
{
	return ((angle * FIELD_OF_VIEW) / WIN_WIDTH);
}

char	ft_get_current_map_char(t_map *map, double x, double y)
{
	int	x_value;
	int	y_value;

	x_value = x / map->texture_size;
	y_value = y / map->texture_size;
	return (map->map_content[y_value][x_value]);
}

double	ft_forward_movement_hits_wall(t_map *map, double v_increase,
	double l_increase)
{
	double		new_v_value;
	double		new_l_value;
	t_vector	*player_pos;
	double		i;

	player_pos = map->prj->player;
	i = 0;
	while (i <= 10)
	{
		new_v_value = player_pos->y - (v_increase / (double)10 * i);
		new_l_value = player_pos->x + (l_increase / (double)10 * i);
		if (ft_get_current_map_char(map, new_l_value, new_v_value) != '0')
			return (1);
		i++;
	}
	return (0);
}

double	ft_backward_movement_hits_wall(t_map *map, double v_increase,
	double l_increase)
{
	double		new_v_value;
	double		new_l_value;
	t_vector	*player_pos;
	double		i;

	player_pos = map->prj->player;
	i = 0;
	while (i <= 10)
	{
		new_v_value = player_pos->y + (v_increase / (double)10 * i);
		new_l_value = player_pos->x - (l_increase / (double)10 * i);
		if (ft_get_current_map_char(map, new_l_value, new_v_value) != '0')
			return (1);
		i++;
	}
	return (0);
}
