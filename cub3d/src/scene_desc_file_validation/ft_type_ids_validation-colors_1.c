#include "../cub3d.h"
#include "../../Libft/libft.h"

int	ft_parse_color_codes(char *line, int *iterator, t_map *map)
{
	int	counter;

	counter = 0;
	while (1)
	{
		if (ft_parse_single_color_code(map, line, iterator) == 1)
			counter++;
		else
			break ;
		if (line[*iterator] != ',')
			break ;
		*iterator += 1;
	}
	if (!ft_isdigit(line[*iterator - 1]))
		ft_invalid_col_statement_error_exit(map, line);
	return (counter);
}

int	ft_parse_single_color_code(t_map *map, char *line, int *iterator)
{
	int		start;
	char	*col_code_str;

	start = *iterator;
	while (line[*iterator] != ',' && !ft_isspace(line[*iterator])
		&& line[*iterator] != '\0')
		*iterator += 1;
	if (*iterator - start == 0)
		return (0);
	col_code_str = ft_substr(line, start, *iterator - start);
	col_code_str = ft_strtrim_no_leaks(col_code_str, " \n");
	ft_validate_col_code_str(map, col_code_str, line);
	return (1);
}

void	ft_validate_col_code_str(t_map *map, char *col_code_str, char *line)
{
	int	color_code;

	color_code = ft_atoi(col_code_str);
	if (!ft_strncmp(col_code_str, "00", 2)
		|| ft_str_is_numeric(col_code_str) == 0
		|| color_code < 0 || color_code > 255)
	{
		ft_free_allocated_map_data(map);
		free(line);
		free(col_code_str);
		ft_putendl_fd("Error: invalid color code", STDERR_FILENO);
		exit(7);
	}
	free(col_code_str);
}
