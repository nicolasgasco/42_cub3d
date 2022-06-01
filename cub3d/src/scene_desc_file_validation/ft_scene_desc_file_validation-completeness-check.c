#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_type_ids_completeness_check(t_map *map)
{
    ft_completeness_check_colors(map);
    ft_completeness_check_o_paths(map);
}

void    ft_completeness_check_colors(t_map *map)
{
    if (!map->c_color || !map->f_color)
    {
        ft_free_allocated_map_data(map);
        ft_putendl_fd("Error: incomplete scene info", STDERR_FILENO);
        exit(9);
    }
    else if (!ft_strncmp(map->c_color, map->f_color, ft_strlen(map->c_color)))
    {
        ft_free_allocated_map_data(map);
        ft_duplicate_scene_info_error_exit();
    }
}

void    ft_completeness_check_o_paths(t_map *map)
{
    if (!map->no_path || !map->ea_path || !map->so_path || !map->we_path)
    {
        ft_free_allocated_map_data(map);
        ft_putendl_fd("Error: incomplete scene info", STDERR_FILENO);
        exit(9);
    }
    ft_check_o_paths_duplicates(map);
 
}

void    ft_check_o_paths_duplicates(t_map *map)
{
    char    **path_arr;
    int     i;
    int     j;

    path_arr = malloc(sizeof(char *) * 4);
    path_arr[0] = map->no_path;
    path_arr[1] = map->ea_path;
    path_arr[2] = map->so_path;
    path_arr[3] = map->we_path;
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            if (j != i && !ft_strncmp(path_arr[i], path_arr[j], ft_strlen(path_arr[i])))
            {
                ft_free_allocated_map_data(map);
                free(path_arr);
                ft_duplicate_scene_info_error_exit();     
            }
            j++;
        }
        i++;
    }
    free(path_arr);
}
