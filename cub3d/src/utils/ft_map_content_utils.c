#include "../cub3d.h"

int	ft_is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	ft_is_valid_map_char(char c)
{
	if (ft_is_player_char(c) || c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

void	ft_check_player_number(t_map *map, int player)
{
	if (player != 1)
		ft_print_error_exit(map, "Error. Incorrect player number.", 15);
}

void	ft_set_player_data(t_map *map, int *iterator, int *j, char c)
{
	map->player_y = (*iterator);
	map->player_x = (*j);
	map->player_orientation = c;
	map->map_content[*iterator][*j] = '0';
}

int	ft_isspace_no_endl(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}
