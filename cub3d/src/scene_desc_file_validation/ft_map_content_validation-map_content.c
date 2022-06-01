#include "../cub3d.h"

void	ft_check_characters(t_map *map)
{
    int	i;
    int	j;

    i = 0;
    while (i < map->height)
    {
	j = 0;
	while (map->map_content[i][j])
	{
	    if (!ft_is_valid_map_char(map->map_content[i][j]))
	    {
		printf("Error. Allowed characters: '1' - '0' - ' ' - 'N' - 'S' - 'E' - 'W'.\n");
		ft_free_map_struct(map);
		exit(14);
	    }
	    j++;
	}
	i++;
    }
}

void	ft_check_player(t_map *map)
{
    int	i;
    int	j;
    int	player;

    i = 0;
    player = 0;
    while (i < map->height)
    {
	j = 0;
	while (map->map_content[i][j])
	{
	    if (ft_is_player_char(map->map_content[i][j]))
		player++;
	    j++;
	}
	i++;
    }
    if (player != 1)
    {
	printf("Error. Incorrect player number.\n");
	ft_free_map_struct(map);
	exit(15);
    }
}

void	ft_vertical_check_inner_void(t_map *map)
{
    int	i;
    int	j;

    i = 0;
    while ((i + 1) < map->height)
    {
	j = 0;
	while (map->map_content[i][j])
	{
	    if (map->map_content[i][j] == ' ' && map->map_content[i + 1][j] == '0')
	    {
		printf("Error. Incorrect map: not surrounded by walls.\n");
		ft_free_map_struct(map);
		exit(16);
	    }
	    if (map->map_content[i][j] == '0' && map->map_content[i + 1][j] == ' ')
	    {
		printf("Error. Incorrect map: not surrounded by walls..\n");
		ft_free_map_struct(map);
		exit(16);
	    }
	    j++;
	}
	i++;
    }
}

void	ft_horizontal_check_inner_void(t_map *map)
{
    int	i;
    int	j;

    i = 0;
    while (i < map->height)
    {
	j = 0;
	while (map->map_content[i][j + 1])
	{
	    if (map->map_content[i][j] == ' ' && map->map_content[i][j + 1] == '0')
	    {
		printf("Error. Incorrect map: not surrounded by walls.\n");
		ft_free_map_struct(map);
		exit(16);
	    }
	    if (map->map_content[i][j] == '0' && map->map_content[i][j + 1] == ' ')
	    {
		printf("Error. Incorrect map: not surrounded by walls..\n");
		ft_free_map_struct(map);
		exit(16);
	    }
	    j++;
	}
	i++;
    }
}

void	ft_validate_content(t_map *map)
{
    ft_check_characters(map);
    ft_check_player(map);
    ft_vertical_check_inner_void(map);
    ft_horizontal_check_inner_void(map);
}
