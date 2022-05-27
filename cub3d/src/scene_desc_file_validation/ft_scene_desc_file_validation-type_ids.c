#include "../cub3d.h"
#include "../../Libft/libft.h"

int    ft_open_scene_file(char *file_path)
{
    int     scene_file_fd;

    scene_file_fd = open(file_path, O_RDONLY);
    if (scene_file_fd == -1)
    {
        ft_putendl_fd("Error: file opening failed", STDERR_FILENO);
		exit(3);
    }
    return(scene_file_fd);  
}

void    ft_type_ids_validation(char *file_path)
{
    int     scene_file_fd;
    char    *line;

    scene_file_fd = ft_open_scene_file(file_path);
    while (1) {
        line = get_next_line(scene_file_fd);
        if (line == NULL)
            break ;
        printf("%s\n", line);
    }
    close(scene_file_fd);
}
