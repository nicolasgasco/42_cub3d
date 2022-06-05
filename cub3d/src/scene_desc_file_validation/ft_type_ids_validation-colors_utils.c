#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_already_existing_color_error(t_map *map, char *color_id, char *line)
{
	if (ft_strncmp(color_id, "F", 1) == 0)
	{
		if (map->f_color)
		{
			free(color_id);
			free(line);
			ft_duplicate_scene_info_error_exit(map);
		}
	}
	else if (ft_strncmp(color_id, "C", 1) == 0)
	{
		if (map->c_color)
		{
			free(color_id);
			free(line);
			ft_duplicate_scene_info_error_exit(map);
		}
	}
}

int	ft_check_if_other_num_same_line(char *line, int iterator)
{
	int	i;

	i = iterator;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}
