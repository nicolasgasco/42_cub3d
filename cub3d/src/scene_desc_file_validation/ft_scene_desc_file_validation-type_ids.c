#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_type_ids_validation(char *file_path)
{
    int     scene_file_fd;
    char    *line;
    int     is_file_empty;
    
    is_file_empty = 1;
    scene_file_fd = ft_open_file(file_path);
    while (1) {
        line = get_next_line(scene_file_fd);
        if (line == NULL)
            break ;
        is_file_empty = 0;
        if (*line == '\n' || !ft_validate_scene_file_line(line))
        {
            free(line);
            return ;
        }
        free(line);
    }
    if (is_file_empty == 1)
    {
        printf("Error: emtpy scene file\n");
        exit(6) ;
    }
    close(scene_file_fd);
}

int    ft_validate_scene_file_line(char *line)
{
    int i;

    i = 0;
    while(line[i] != '\0')
    {
        ft_skip_to_non_space_char(line, &i);
        if (line[i] == 'N' || line[i] == 'S'
            || line[i] == 'W' || line[i] == 'E')
        {
            ft_parse_orientation_path(line, &i);
            break;
        }
        else if (line[i] == 'F' || line[i] == 'C')
        {
            ft_parse_colors(line, &i);
            break;
        }
        else if (line[i] == '1')
            return (0);
        else
        {
            free(line);
            ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
            exit(4);
        }
        i++;
    }
    return (1);
}
