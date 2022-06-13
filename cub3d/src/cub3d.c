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
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_scene_desc_file_validation(argc, argv[1], &map);
	ft_raycasting_calculation(&map);
	ft_free_allocated_map_data(&map);
	return (0);
}
