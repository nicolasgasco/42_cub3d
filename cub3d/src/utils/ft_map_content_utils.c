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

int	ft_is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_is_valid_map_char(char c)
{
	if (ft_is_player_char(c) || c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

void	ft_check_player_number(t_map *map, int player)
{
	if (player != 1)
		ft_print_error_exit(map, "Error. Incorrect player number.", 15);
}

void	ft_set_player_data(t_map *map, int *iterator, int *j, char c)
{
	t_projection projection;

	ft_memset(&projection, 0, sizeof(t_projection));
	map->projection = &projection;
	map->projection->player_y = (*iterator);
	map->projection->player_x = (*j);
	map->projection->player_orientation = c;
	map->map_content[*iterator][*j] = '0';
}

int	ft_isspace_no_endl(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}
