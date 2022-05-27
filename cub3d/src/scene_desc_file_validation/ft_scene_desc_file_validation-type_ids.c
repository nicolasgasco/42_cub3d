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
        ft_validate_scene_file_line(line);
        break;
    }
    close(scene_file_fd);
}

void    ft_validate_scene_file_line(char *line)
{
    int i;

    i = 0;
    while(line[i] != '\0')
    {
        ft_skip_to_non_space_char(line, &i);
        printf("%c", line[i]);
        if (line[i] == '1')
        {
            printf("Logic for map\n");
            return ;
        }
        else if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'W' || line[i] == 'E')
        {
            ft_validate_orientation_path(line, &i);
            break;
        }
        else if (line[i] == 'F' || line[i] == 'C')
        {
            printf("Logic for Color validation");
            break;
        }
        else
        {
            ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
            exit(5);
        }
        i++;
    }
    printf("\n");
}
