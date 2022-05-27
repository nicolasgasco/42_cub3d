#include "../cub3d.h"

void    ft_type_ids_validation(char *file_path)
{
    int     scene_file_fd;
    char    *line;

    scene_file_fd = open(file_path, O_RDONLY);
    while (1) {
        line = get_next_line(scene_file_fd);
        if (line == NULL)
            break ;
        printf("%s\n", line);
    }
    close(scene_file_fd);
}
