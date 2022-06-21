#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_render_whole_scene(t_view *view, t_map *map)
{
	if (view->plane_data->img)
		mlx_destroy_image(view->mlx, view->plane_data->img);
	view->plane_data->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	ft_raycasting_calculation(map, view);
}

void    ft_render_column(t_view *view, t_map *map)
{
    int j;
    int i;
    int half_h;

	view->plane_data->addr = mlx_get_data_addr(view->plane_data->img, &view->plane_data->bits_per_pixel, &view->plane_data->line_length, &view->plane_data->endian);
	printf("\x1b[33mColumn is %d, Height is %d\x1b[0m\n", map->slc->column, map->slc->height);
	if (map->slc->height < 0)
		map->slc->height = 0; // TBD - Only for debug
	half_h = (PROJ_PLANE_HEIGHT - map->slc->height) / 2;
    j = 0;
	while (j < half_h)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, j, map->rdata->c_col_int);
		j++;
	}
	i = 0;
	while (i < map->slc->height && j < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, j, 0x22E100);
		i++;
		j++;
	}
	if (j == 0)
		j = half_h; // TBD - Only for debug
	while (j < PROJ_PLANE_HEIGHT)
	{
		my_mlx_pixel_put(view->plane_data, map->slc->column, j, map->rdata->f_col_int);
		j++;
	}
}

void ft_render_texture(t_view *view, t_tdata *texture, int win_x, int win_y)
{
	t_data img;
	int y;
	int x;

	img.img = mlx_new_image(view->mlx, texture->texture_w, texture->texture_h);
	printf("Bits %d, line_length %d, endian %d\n", img.bits_per_pixel, img.line_length, img.endian);
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
