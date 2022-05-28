#include "../cub3d.h"
#include "../../Libft/libft.h"

int    ft_open_file(char *file_path)
{
    int     file_fd;

    file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1)
    {
        free(file_path);
        ft_open_file_error();
    }
    return(file_fd);  
}

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

void    ft_skip_to_non_space_char(char *line, int *iterator)
{
    while(line[*iterator] != '\0')
    {
        if (ft_isspace(line[*iterator]))
            *iterator += 1;
        else
            return;
    }
}
