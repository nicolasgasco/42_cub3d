#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_parse_colors(char *line, int *i, t_map *map)
{
    char    *color_char;

    color_char = ft_substr(line, *i, 1);
    *i = *i + 1;
    if (ft_strncmp(color_char, "F", 1) == 0)
    {
        if (map->f_color)
        {
            ft_free_allocated_map_data(map);
            free(color_char);
            free(line);
            ft_duplicate_scene_info_error_exit();     
        }
        map->f_color = ft_validate_colors(color_char, line, i, map);
    }
    else if (ft_strncmp(color_char, "C", 1) == 0)
    {
        if (map->c_color)
        {
            ft_free_allocated_map_data(map);
            free(color_char);
            free(line);
            ft_duplicate_scene_info_error_exit();     
        }
        map->c_color = ft_validate_colors(color_char, line, i, map);
    }
}

char    *ft_validate_colors(char *color_char, char *line, int *i, t_map *map)
{
    int     codes_count;
    int     c_stat_start;

    codes_count = 0;
    free(color_char);
    if (!ft_isspace(line[*i]) && line[*i] != '\0')
        ft_invalid_id_error_exit(line);
    ft_skip_to_non_space_char(line, i);
    c_stat_start = *i;
    codes_count = ft_parse_color_codes(line, i, map);
    if (codes_count != 3)
    {
        free(line);
        ft_putendl_fd("Error: invalid color statement", STDERR_FILENO);
        exit(8);
    }
    return (ft_substr(line, c_stat_start, *i - c_stat_start));
}

int ft_parse_color_codes(char *line, int *iterator, t_map *map)
{
    int counter;

    counter = 0;
    while (1)
    {
        if (ft_parse_single_color_code(line, iterator) == 1)
            counter++;
        else
            break;
        if (line[*iterator] != ',')
            break;
        *iterator += 1;
    }
    if (!ft_isdigit(line[*iterator - 1]))
    {
        ft_free_allocated_map_data(map);
        free(line);
        ft_putendl_fd("Error: invalid color statement", STDERR_FILENO);
        exit(8);
    }
    return (counter);
}

int    ft_parse_single_color_code(char *line, int *iterator)
{
    int     start;
    char    *color_code_str;

    start = *iterator;
    while (line[*iterator] != ',' && !ft_isspace(line[*iterator]) && line[*iterator] != '\0')
        *iterator += 1;
    if (*iterator - start == 0)
        return (0);
    color_code_str = ft_substr(line, start, *iterator - start);
    color_code_str = ft_strtrim_no_leaks(color_code_str, " \n");

    ft_validate_color_code_str(color_code_str, line);
    return (1);
}

void    ft_validate_color_code_str(char *color_code_str, char *line)
{
    int color_code;

    color_code = ft_atoi(color_code_str);
    if (ft_str_is_numeric(color_code_str) == 0 || color_code < 0 || color_code > 255)
    {
        free(line);
        free(color_code_str);
        ft_putendl_fd("Error: invalid color code", STDERR_FILENO);
        exit(7);
    }
    free(color_code_str);
}
