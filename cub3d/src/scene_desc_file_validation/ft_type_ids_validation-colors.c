/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_desc_file_validation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/06/09 13:14:58 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_validate_parse_color(char *line, int *i, t_map *map)
{
	char	*color_id;

	if (line[*i + 1] && !ft_isspace(line[*i + 1]))
		ft_invalid_id_error_exit(map, line);
	color_id = ft_substr(line, *i, 1);
	*i = *i + 1;
	if (ft_strncmp(color_id, "F", 1) == 0)
	{
		ft_already_existing_color_error(map, color_id, line);
		map->f_color = ft_validate_colors(color_id, line, i, map);
	}
	else if (ft_strncmp(color_id, "C", 1) == 0)
	{
		ft_already_existing_color_error(map, color_id, line);
		map->c_color = ft_validate_colors(color_id, line, i, map);
	}
}

char	*ft_validate_colors(char *color_id, char *line, int *i, t_map *map)
{
	int		codes_count;
	int		c_stat_start;
	char	*col_statement;

	codes_count = 0;
	free(color_id);
	if (!ft_isspace(line[*i]) && line[*i] != '\0')
		ft_invalid_id_error_exit(map, line);
	ft_skip_to_non_space_char(line, i);
	c_stat_start = *i;
	codes_count = ft_parse_color_codes(line, i, map);
	if (ft_check_if_other_num_same_line(line, *i) || codes_count != 3)
		ft_invalid_col_statement_error_exit(map, line);
	col_statement = ft_substr(line, c_stat_start, *i - c_stat_start);
	return (col_statement);
}

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
	ft_validate_single_col_code(map, col_code_str, line);
	return (1);
}

void	ft_validate_single_col_code(t_map *map, char *col_code_str, char *line)
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
