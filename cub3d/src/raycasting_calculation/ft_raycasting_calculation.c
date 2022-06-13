#include "../cub3d.h"
#include <math.h>

void	ft_horizontal_intersection(t_map *map)
{
	double Ay;
//	double Ax;

	if (map->projection->player_orientation == 'N' || map->projection->player_orientation == 'E')
		Ay = floor(((map->projection->player_y * CUBE_SIZE) + (CUBE_SIZE / 2)) / CUBE_SIZE) * (CUBE_SIZE) - 1;
	//else if (map->projection->player_orientation == 'S' || map->projection->player_orientation == 'W')
	//	Ay = floor(
	printf("Ay: %f\n", Ay);
}

void	ft_raycasting_calculation(t_map *map)
{
	printf("Px: %i, Py: %i, PO: %c\n", map->projection->player_x, map->projection->player_y, map->projection->player_orientation);
	ft_horizontal_intersection(map);
//	ft_vertical_intersection(map);
}
