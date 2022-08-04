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
	if (!ft_xpm_file_is_valid(map, map->no_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map, map->ea_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map, map->so_path, mlx))
		is_error = 1;
	if (!ft_xpm_file_is_valid(map, map->we_path, mlx))
		is_error = 1;
	if (is_error == 1)
		ft_texture_file_invalid(map);
	free(mlx);
}

int	ft_xpm_file_is_valid(t_map *map, char *path, void *mlx)
{
	void	*img;
	int		size;

	size = ft_get_texture_size(map, path);
	if (size < 32 || size > 512)
		ft_texture_file_invalid(map);
	if (map->texture_size && size != map->texture_size)
		ft_texture_file_invalid(map);
	else
		map->texture_size = size;
	img = mlx_xpm_file_to_image(mlx, path, &size, &size);
	if (img == NULL)
		return (0);
	else
		mlx_destroy_image(mlx, img);
	return (1);
}

int	ft_get_texture_size(t_map *map, char *path)
{
	int		file_fd;
	char	*line;
	int		i;

	file_fd = open(path, O_RDONLY);
	if (file_fd == -1)
	{
		ft_free_allocated_map_data(map);
		ft_open_file_error();
	}
	i = 0;
	while (1)
	{
		line = get_next_line(file_fd);
		if (i == 3)
			break;
		if (line == NULL)
			return (0);
		free(line);
		i++;
	}
	return (ft_parse_texture_size(line));
	free(line);
	close(file_fd);
}

int	ft_parse_texture_size(char *line)
{
	int		i;
	char	*result_string;
	int		result;

	i = 0;
	while (line[i] != '0')
	{
		if (ft_isspace(line[i]))
			break;
		i++;
	}
	result_string = ft_substr(line, 1, i - 1);
	result = ft_atoi(result_string);
	free(result_string);
	return (result);
}