/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_data_manip-asset_validation.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/19 12:51:49 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_validate_texture_files(t_map *map)
{
	void	*mlx;
	int		is_error;

	is_error = 0;
	mlx = mlx_init();
	if (!ft_xpm_file_is_valid(map->no_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map->ea_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map->so_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map->we_path, mlx))
		is_error = 1;
	if (is_error == 1)
	{
		ft_free_allocated_map_data(map);
		ft_free_allocated_render_data(map->rdata);
		ft_putendl_fd("Error: texture file is invalid", STDERR_FILENO);
		exit(1000);
	}
	free(mlx);
}

int	ft_xpm_file_is_valid(char *path, void *mlx)
{
	void	*img;
	int		size;

	size = TEXTURE_SIZE;
	img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	if (img == NULL)
		return (0);
	else
		mlx_destroy_image(mlx, img);
	return (1);
}
