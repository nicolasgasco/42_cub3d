#include "../cub3d.h"

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
