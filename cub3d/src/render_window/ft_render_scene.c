#include "../cub3d.h"
#include "../../Libft/libft.h"

void ft_render_game_scene(t_view *view, t_map *map)
{
	if (view->plane_data->img)
		mlx_destroy_image(view->mlx, view->plane_data->img);
	view->plane_data->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_raycasting_calculation(map, view);
}

void ft_render_raycasting_column(t_view *view, t_map *map)
{
	int 	y;
	t_data	*plane;

	plane = view->plane_data;
	plane->addr = mlx_get_data_addr(plane->img, &plane->bits_per_pixel, &plane->line_length, &plane->endian);
	printf("\x1b[33mColumn is %d, Height is %d\x1b[0m\n", map->slc->column, map->slc->height);  // TBD - Only for debug
	if (map->slc->height < 0) // TBD - Only for debug
		map->slc->height = 0; // TBD - Only for debug
	y = 0;
	ft_render_ceiling(view, map, &y);
	ft_render_scaled_texture(view, map, &y); // Commented if you want to see raycasting without textures
	// ft_render_solid_color(view, map, &y); // Uncommented if you want to see raycasting without textures
	ft_render_floor(view, map, &y);
}

void	ft_render_ceiling(t_view *view, t_map *map, int *y)
{
	int 	offset;

	offset = (PROJ_PLANE_HEIGHT - map->slc->height) / 2;
	while (*y < offset)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, *y, map->rdata->c_col_int);
		*y += 1;
	}
	if (*y == 0) // TBD - Only for debug
		*y = offset; // TBD - Only for debug
}

void	ft_render_floor(t_view *view, t_map *map, int *y)
{
	while (*y < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, *y, map->rdata->f_col_int);
		*y += 1;
	}
}

/* Use this if you want to see raycasting without textures */
void ft_render_solid_color(t_view *view, t_map *map, int *y)
{
	int i;

	i = 0;
	while (i < map->slc->height && *y < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, *y, 0x22E100);
		i += 1;
		*y += 1;
	}
}

/* Used for testing only. Renders one texture in 2d */
void ft_render_texture(t_view *view, t_tdata *texture, int win_x, int win_y)
{
	t_data img;
	int y;
	int x;

	img.img = mlx_new_image(view->mlx, texture->texture_w, texture->texture_h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	y = 0;
	while (y < texture->texture_h)
	{
		x = 0;
		while (x < texture->texture_w)
		{
			my_mlx_pixel_put(&img, x, y, texture->texture_columns[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(view->mlx, view->mlx_win, img.img, win_x, win_y);
}
