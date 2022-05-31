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
	t_map    map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_check_num_args(argc);
	ft_scene_desc_file_validation(argv[1], &map);
	free(map.ea_path); // TODO free when opportune
	free(map.we_path); // TODO free when opportune
	free(map.no_path); // TODO free when opportune
	free(map.so_path); // TODO free when opportune
	free(map.c_color); // TODO free when opportune
	free(map.f_color); // TODO free when opportune
	return (0);
}
