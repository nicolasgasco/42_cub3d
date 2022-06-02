#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_check_vertical_wall(int wall, t_map *map)
{
    int	i;
    int	j;

    i = 0;
    while (i < map->height)
    {
	j = wall;
	if (wall == 0)
	    ft_skip_to_non_space_char(map->map_content[i], &j);
	else
	    ft_skip_to_non_space_char_backwards(map->map_content[i], &j);
	if (map->map_content[i][j] != '1')
	{
		ft_putendl_fd("Error. Incorrect map: not surrounded by walls.", STDERR_FILENO);
	    ft_free_map_struct(map);
	    exit(13);
	}
	i++;
    }
}

void	ft_check_horizontal_wall(int wall, t_map *map)
{
    int	i;
    int	j;

    i = 0;
	ft_skip_to_non_space_char(map->map_content[wall], &i);
    while (i < map->width - 1)
    {
    	j = wall;
	while (map->map_content[j][i] == ' ')
	{
	    if (wall == 0)
	    	j++;
	    else
		j--;
	}
	if (map->map_content[j][i] != '1')
	{
		ft_putendl_fd("Error. Incorrect map: not surrounded by walls.", STDERR_FILENO);
	    ft_free_map_struct(map);
	    exit(13);
	}
	i++;
    }
}

void	ft_validate_walls(t_map *map)
{
    ft_check_vertical_wall(0, map);
    ft_check_vertical_wall((map->width - 1), map);
    ft_check_horizontal_wall(0, map);
    ft_check_horizontal_wall((map->height - 1), map);
}