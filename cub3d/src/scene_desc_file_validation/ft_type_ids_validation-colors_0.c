#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_parse_colors(char *line, int *i, t_map *map)
{
	char	*color_id;

	if (line[*i + 1] && !ft_isspace(line[*i + 1]))
		ft_invalid_id_error_exit(map, line);
	color_id = ft_substr(line, *i, 1);
	*i = *i + 1;
	if (ft_strncmp(color_id, "F", 1) == 0)
	{
		ft_check_if_color_already_exists(map, color_id, line);
		map->f_color = ft_validate_colors(color_id, line, i, map);
	}
	else if (ft_strncmp(color_id, "C", 1) == 0)
	{
		ft_check_if_color_already_exists(map, color_id, line);
		map->c_color = ft_validate_colors(color_id, line, i, map);
	}
}

void	ft_check_if_color_already_exists(t_map *map, char *color_id, char *line)
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

char	*ft_validate_colors(char *color_id, char *line, int *i, t_map *map)
{
	int	codes_count;
	int	c_stat_start;

	codes_count = 0;
	free(color_id);
	if (!ft_isspace(line[*i]) && line[*i] != '\0')
		ft_invalid_id_error_exit(map, line);
	ft_skip_to_non_space_char(line, i);
	c_stat_start = *i;
	codes_count = ft_parse_color_codes(line, i, map);
	if (ft_check_if_other_num_same_line(line, *i) || codes_count != 3)
		ft_invalid_col_statement_error_exit(map, line);
	return (ft_substr(line, c_stat_start, *i - c_stat_start));
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
