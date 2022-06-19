#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <math.h>

/*ft_set_coords_angle_direction_horizontal sets the starting values 
 * for rc->horizontal y & x based on the angle orientation*/

void	ft_set_coords_angle_direction_horizontal(t_map *map)
{
	t_vector	*horizontal;

	horizontal = malloc(sizeof(t_vector));
	ft_memset(horizontal, 0, sizeof(t_vector));
	map->prj->rc_horizontal = horizontal;
	if (map->prj->view_angle > 0
		&& map->prj->view_angle < 180)
		map->prj->rc_horizontal->y = floor(map->prj->player->y
				/ CUBE_SIZE) * (CUBE_SIZE) - 1;
	else
		map->prj->rc_horizontal->y = floor(map->prj->player->y
				/ CUBE_SIZE) * (CUBE_SIZE) + CUBE_SIZE;
	map->prj->rc_horizontal->x = map->prj->player->x
		+ (map->prj->player->y - map->prj->rc_horizontal->y)
		/ tan(map->prj->view_angle * (PI / 180));
}

/*ft_set_coords_angle_direction_vertical sets the starting values 
 * for rc->vertical y & x based on the angle orientation*/

void	ft_set_coords_angle_direction_vertical(t_map *map)
{
	t_vector	*vertical;

	vertical = malloc(sizeof(t_vector));
	ft_memset(vertical, 0, sizeof(t_vector));
	map->prj->rc_vertical = vertical;
	if (map->prj->view_angle > 270 && map->prj->view_angle < 90)
		map->prj->rc_vertical->x = floor(map->prj->player->x
				/ CUBE_SIZE) * (CUBE_SIZE) + CUBE_SIZE;
	else
		map->prj->rc_vertical->x = floor(map->prj->player->x
				/ CUBE_SIZE) * (CUBE_SIZE) - 1;
	map->prj->rc_vertical->y = map->prj->player->y
		+ (map->prj->player->x - map->prj->rc_vertical->x)
		/ tan(map->prj->view_angle * (PI / 180));
}

/*ft_convert_to_cube_position sets the player position in the 
 * projection dimension*/

void	ft_convert_to_cube_position(t_map *map)
{
	map->prj->player->y = (map->prj->player->y * CUBE_SIZE) + (CUBE_SIZE / 2);
	map->prj->player->x = (map->prj->player->x * CUBE_SIZE) + (CUBE_SIZE / 2);
}

/*ft_set_viewing_angle returns the angle of the view based on 
 * the player orientation*/

double	ft_set_viewing_angle(char c)
{
	if (c == 'E')
		return (0);
	else if (c == 'N')
		return (90);
	else if (c == 'W')
		return (180);
	else
		return (270);
}

/*ft_set_player_data creates and fills the structure for the 
 * projection with the data from the given map*/

void	ft_set_player_data(t_map *map, int *iterator, int *j, char c)
{
	map->prj->player->y = (*iterator);
	map->prj->player->x = (*j);
	map->prj->player_orientation = c;
	map->prj->view_angle = ft_set_viewing_angle(c);
	map->prj->distance_to_pp = (PROJ_PLANE_WIDTH / 2)
		/ tan((FIELD_OF_VIEW / 2) * (PI / 180));
	map->prj->angle_btw_rays = FIELD_OF_VIEW / PROJ_PLANE_WIDTH;
	map->map_content[*iterator][*j] = '0';
}
