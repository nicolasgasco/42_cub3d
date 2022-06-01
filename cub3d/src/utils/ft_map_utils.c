#include "../cub3d.h"

int    ft_is_map_start(char *line)
{
    int    i;

    i = 0;
    ft_skip_to_non_space_char(line, &i);
    if (line[i] == '1')
	return (1);
    return (0);
}

void    ft_get_map_width(char *line, t_map *map)
{
    int    i;

    i = 0;
    while (line[i] != '\n')
    {
        i++;
	if (i > map->width)
	    map->width = i;
    }
}

char    *ft_skip_to_map_start(char *line, int fd)
{
    while (line)
    {
	if (ft_is_map_start(line) == 0)
	{
	    free(line);
	    line = get_next_line(fd);
	}
	else
	    break ;
    }
    return (line);
}

void    ft_skip_to_non_space_char_backwards(char *line, int *iterator)
{
    while(*iterator != 0)
    {
        if (ft_isspace(line[*iterator]))
            *iterator -= 1;
        else
            return;
    }
}

void	ft_free_map_struct(t_map *map)
{
    int	i;

    i = 0;
    while (i < map->height)
    {
	if (map->map_content[i])
	    free(map->map_content[i]);
	i++;
    }
    if (map->map_content)
	free(map->map_content);
}
