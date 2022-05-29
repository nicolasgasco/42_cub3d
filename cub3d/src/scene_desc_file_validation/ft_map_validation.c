#include "../cub3d.h"
#include "../../Libft/libft.h"

int	ft_map_validation(char *line, t_map_data *map)
{
    int    i;

    i = 0;
    map->count = 0;
    map->max_width = 0;
    map->content = (char **) malloc (sizeof(char *));
    while (line[i])
	i++;
    map->content[map->count] = (char *) malloc (i);
    map->count++;
    i = 0;
    return (0);
}
