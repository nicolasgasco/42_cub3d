/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:15:12 by jsolinis          #+#    #+#             */
/*   Updated: 2022/05/22 23:15:59 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map			map;
	t_projection	projection;
	t_vector		player;
	t_map	map;
	t_view	view;

	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&projection, 0, sizeof(t_projection));
	ft_memset(&player, 0, sizeof(t_vector));
	map.prj = &projection;
	map.prj->player = &player;
	ft_scene_desc_file_validation(argc, argv[1], &map);
	ft_raycasting_calculation(&map);
	ft_free_allocated_map_data(&map);
	ft_memset(&view, 0, sizeof(t_view));
	ft_render_view(&view);
	return (0);
}
