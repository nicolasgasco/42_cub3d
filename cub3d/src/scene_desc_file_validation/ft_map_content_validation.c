#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_set_map_line(char *line, t_map *map, int *iterator)
{
    int	j;

    j = 0;
    map->map_content[*iterator] = (char *) malloc ((map->width + 1) * sizeof(char));
    while (line[j] != '\n')
    {
	map->map_content[*iterator][j] = line[j];
	j++;
    }
    while (j < map->width)
    {
	map->map_content[*iterator][j] = ' ';
	j++;
    }
    map->map_content[*iterator][j] = '\0';
}

void    ft_set_map_content(char *file_path, t_map *map)
{
    int     fd;
    int     i;
    char    *line;

    i = 0;
    fd = ft_open_file(file_path);
    map->map_content = (char **) malloc (map->height * sizeof(char *));
    line = get_next_line(fd);
    line = ft_skip_to_map_start(line, fd);
    while (i < map->height)
    {
        ft_set_map_line(line, map, &i);
	free(line);
	line = get_next_line(fd);
	i++;
    }
    free(line);
    close(fd);
}

void	ft_get_map_size(char *file_path, t_map *map)
{
    int     fd;
    char    *line;

    fd = ft_open_file(file_path);
    line = get_next_line(fd);
    line = ft_skip_to_map_start(line, fd);
    while (line)
    {
	map->height++;
	ft_get_map_width(line, map);
	free(line);
	line = get_next_line(fd);
    }
    free(line);
    close(fd);
}

void    ft_map_content_validation(char *file_path, t_map *map)
{
    ft_get_map_size(file_path, map);
    ft_set_map_content(file_path, map);
    ft_validate_size(map);
    ft_validate_walls(map);
    ft_validate_content(map);
}
