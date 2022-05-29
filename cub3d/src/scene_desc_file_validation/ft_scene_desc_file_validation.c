#include "../cub3d.h"

void ft_scene_desc_file_validation(char *file_path)
{
    ft_file_extension_validation(file_path);
    ft_type_ids_validation(file_path);
}
