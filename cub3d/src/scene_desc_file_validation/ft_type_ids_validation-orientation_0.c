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
	o_path = ft_parse_path(map, o_path_id, line, i);
	return (o_path);
}
