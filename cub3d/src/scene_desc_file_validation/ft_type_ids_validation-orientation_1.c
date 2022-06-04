#include "../cub3d.h"
#include "../../Libft/libft.h"

char	*ft_parse_path(t_map *map, char *o_path_id, char *line, int *i)
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
