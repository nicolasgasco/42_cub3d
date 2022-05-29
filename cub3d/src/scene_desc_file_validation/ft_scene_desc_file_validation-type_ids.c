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
        if (*line == '\n')
        {
            free(line);
            continue ;
        }
        ft_validate_scene_file_line(line);
        free(line);
    }
    if (is_file_empty == 1)
    {
        printf("Error: emtpy scene file\n");
        exit(6) ;
    }
    close(scene_file_fd);
}

void    ft_validate_scene_file_line(char *line)
{
    int i;

    i = 0;
    printf("Validating line |%s| -> ", line);
    while(line[i] != '\0')
    {
        ft_skip_to_non_space_char(line, &i);
        if (line[i] == '1')
        {
            printf("Logic for map\n");
            free(line); // TODO delete this
            exit(101) ; // TODO delete this
        }
        else if (line[i] == 'N' || line[i] == 'S'
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
        else
        {
            free(line);
            ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
            exit(4);
        }
        i++;
    }
    printf("\n");
}
