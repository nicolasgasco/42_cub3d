#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_type_ids_completeness_check(t_map *map)
{
    ft_completeness_check_colors(map);
}

void    ft_completeness_check_colors(t_map *map)
{
    if (!map->c_color || !map->f_color)
    {
        free(map->ea_path); // TODO refactor this
        free(map->we_path); // TODO refactor this
        free(map->no_path); // TODO refactor this
        free(map->so_path); // TODO refactor this
        free(map->c_color); // TODO refactor this
        free(map->f_color); // TODO refactor this
        ft_putendl_fd("Error: incomplete scene info", STDERR_FILENO);
        exit(9);
    }
    else if (!ft_strncmp(map->c_color, map->f_color, ft_strlen(map->c_color)))
    {
        free(map->ea_path); // TODO refactor this
        free(map->we_path); // TODO refactor this
        free(map->no_path); // TODO refactor this
        free(map->so_path); // TODO refactor this
        free(map->c_color); // TODO refactor this
        free(map->f_color); // TODO refactor this
        ft_putendl_fd("Error: duplicated scene info", STDERR_FILENO);
        exit(10);       
    }
}
