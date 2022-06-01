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
