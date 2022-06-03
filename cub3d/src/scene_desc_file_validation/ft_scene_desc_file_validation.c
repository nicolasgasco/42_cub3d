#include "../cub3d.h"

void ft_scene_desc_file_validation(char *file_path, t_map *map)
{
    ft_write_debug_msg("Starting validation");
    ft_file_extension_validation(file_path);
    ft_type_ids_validation(file_path, map);
    ft_type_ids_completeness_check(map);
    ft_write_debug_msg("Type ids validated successfully");
    ft_map_content_validation(file_path, map);
    ft_write_debug_msg("Scene file validated successfully");
}
