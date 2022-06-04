#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_invalid_id_error_exit(t_map *map, char *line)
{
    free(line);
    ft_free_allocated_map_data(map);
    ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
    exit(4);
}

void    ft_duplicate_scene_info_error_exit(t_map *map)
{
    ft_free_allocated_map_data(map);
    ft_putendl_fd("Error: duplicated scene info", STDERR_FILENO);
    exit(10);
}

void    ft_invalid_col_statement_error_exit(t_map *map, char *line)
{
    free(line);
    ft_free_allocated_map_data(map);
    ft_putendl_fd("Error: invalid color statement", STDERR_FILENO);
    exit(8);
}

void    ft_incomplete_scene_info_error_exit(t_map *map)
{
    ft_free_allocated_map_data(map);
    ft_putendl_fd("Error: incomplete scene info", STDERR_FILENO);
    exit(9);
}
