#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_parse_orientation_path(char *line, int *i, t_map *map)
{
	char	*o_path_id;

	o_path_id = ft_substr(line, *i, 2);
	*i = *i + 2;
	if (!ft_check_if_map_o_path_unassigned(map, o_path_id))
	{
		free(o_path_id);
		free(line);
		ft_duplicate_scene_info_error_exit(map);
	}
	if (ft_strncmp(o_path_id, "NO", 2) == 0)
		map->no_path = ft_validate_o_path(map, o_path_id, line, i);
	else if (ft_strncmp(o_path_id, "SO", 2) == 0)
		map->so_path = ft_validate_o_path(map, o_path_id, line, i);
	else if (ft_strncmp(o_path_id, "WE", 2) == 0)
		map->we_path = ft_validate_o_path(map, o_path_id, line, i);
	else if (ft_strncmp(o_path_id, "EA", 2) == 0)
		map->ea_path = ft_validate_o_path(map, o_path_id, line, i);
	else
	{
		free(o_path_id);
		ft_invalid_id_error_exit(map, line);
	}
	free(o_path_id);
}

int	ft_check_if_map_o_path_unassigned(t_map *map, char *o_path_id)
{
	if (ft_strncmp(o_path_id, "NO", 2) == 0)
	{
		if (map->no_path)
			return (0);
	}
	else if (ft_strncmp(o_path_id, "SO", 2) == 0)
	{
		if (map->so_path)
			return (0);
	}
	else if (ft_strncmp(o_path_id, "WE", 2) == 0)
	{
		if (map->we_path)
			return (0);
	}
	else if (ft_strncmp(o_path_id, "EA", 2) == 0)
	{
		if (map->ea_path)
			return (0);
	}
	return (1);
}

char	*ft_validate_o_path(t_map *map, char *o_path_id, char *line, int *i)
{
	char	*o_path;
	int		o_file_fd;

	if (!ft_isspace(line[*i]))
	{
		free(o_path_id);
		ft_invalid_id_error_exit(map, line);
	}
	ft_skip_to_non_space_char(line, i);
	if (line[*i] == '\0')
	{
		free(o_path_id);
		free(line);
		ft_free_allocated_map_data(map);
		ft_putendl_fd("Error: missing file path", STDERR_FILENO);
		exit(6);
	}
	o_path = ft_substr(line, *i, ft_calc_path_length(line, *i));
	*i += ft_calc_path_length(line, *i);
	o_path = ft_strtrim_no_leaks(o_path, " \n");
	o_file_fd = ft_validate_f_path(map, o_path, line, o_path_id);
	close(o_file_fd);
	ft_skip_to_non_space_char(line, i);
	if (!ft_isspace(line[*i]) && line[*i] != '\0')
	{
		ft_free_allocated_map_data(map);
		free(line);
		free(o_path_id);
		free(o_path);
		ft_putendl_fd("Error: invalid orientation path statement", STDERR_FILENO);
		exit(17);
	}
	return (o_path);
}

int	ft_calc_path_length(char *line, int i)
{
	int	len;

	len = 0;
	while (ft_isspace(line[i]) == 0 && line[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	ft_validate_f_path(t_map *map, char *o_path, char *line, char *o_path_id)
{
	int	file_fd;

	file_fd = open(o_path, O_RDONLY);
	if (file_fd == -1)
	{
		ft_free_allocated_map_data(map);
		free(o_path);
		free(line);
		free(o_path_id);
		ft_open_file_error();
	}
	return (file_fd);
}
