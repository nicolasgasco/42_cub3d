#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_type_ids_validation(char *file_path, t_map *map)
{
	int		scene_file_fd;
	char	*line;
	int		is_file_empty;

	is_file_empty = 1;
	scene_file_fd = open(file_path, O_RDONLY);
	if (scene_file_fd == -1)
		ft_open_file_error();
	while (1)
	{
		line = get_next_line(scene_file_fd);
		if (line == NULL)
			break ;
		is_file_empty = 0;
		if (!ft_validate_scene_file_line(line, map))
		{
			free(line);
			return ;
		}
		free(line);
	}
	if (is_file_empty == 1)
		ft_empty_scene_file_error_exit();
	close(scene_file_fd);
}

int	ft_validate_scene_file_line(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		ft_skip_to_non_space_char(line, &i);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
		{
			ft_parse_orientation_path(line, &i, map);
			break ;
		}
		else if (line[i] == 'F' || line[i] == 'C')
		{
			ft_parse_colors(line, &i, map);
			break ;
		}
		else if (line[i] == '1')
			return (0);
		else if (line[i] == '\0')
			break ;
		else
			ft_invalid_id_error_exit(map, line);
		i++;
	}
	return (1);
}
