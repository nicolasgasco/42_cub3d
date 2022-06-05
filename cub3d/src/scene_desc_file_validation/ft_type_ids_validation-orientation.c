#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_validate_parse_o_path(char *line, int *i, t_map *map)
{
	char	*o_path_id;

	o_path_id = ft_substr(line, *i, 2);
	*i = *i + 2;
	if (ft_check_o_path_already_assigned(map, o_path_id) == 1)
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

char	*ft_validate_o_path(t_map *map, char *o_path_id, char *line, int *i)
{
	char	*o_path;

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
	o_path = ft_parse_valid_path(map, o_path_id, line, i);
	return (o_path);
}

char	*ft_parse_valid_path(t_map *map, char *o_path_id, char *line, int *i)
{
	int		o_file_fd;
	char	*o_path;

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
		ft_putendl_fd("Error: invalid orientation path", STDERR_FILENO);
		exit(17);
	}
	return (o_path);
}
