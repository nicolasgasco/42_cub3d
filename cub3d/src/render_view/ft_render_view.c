#include "../cub3d.h"
#include "../../Libft/libft.h"
#include <time.h>

void ft_render_view(t_view *view)
{
	view->width = GAME_WIDTH;
	view->height = GAME_HEIGHT;
	view->title = ft_strdup(GAME_TITLE);
	view->mlx = mlx_init();
	view->mlx_win = mlx_new_window(view->mlx, view->width,
								   view->height, view->title);
	ft_view_events(view);
	mlx_loop(view->mlx);
}

void ft_xpm_data_poc(t_view *view, int ver)
{
	char *xpm_data[GAME_HEIGHT + 10];
	int width = 10;
	int height = 5;
	void *image = NULL;
	clock_t t;
	t = clock();
	xpm_data[0] = ft_strdup(ft_itoa(GAME_WIDTH - 3));
	xpm_data[0] = ft_strjoin(xpm_data[0], " ");
	xpm_data[0] = ft_strjoin(xpm_data[0], ft_itoa(GAME_HEIGHT - 3));
	xpm_data[0] = ft_strjoin(xpm_data[0], " 4 1");
	if (ver == 1)
	{
		xpm_data[1] = ft_strdup(". c #00FFFF");
		xpm_data[2] = ft_strdup(", c #FF0000");
		xpm_data[3] = ft_strdup("a c #BB00BB");
		xpm_data[4] = ft_strdup("b c #CCDD00");
	}
	else
	{
		xpm_data[1] = ft_strdup(". c #FF0000");
		xpm_data[2] = ft_strdup(", c #00FFFF");
		xpm_data[3] = ft_strdup("a c #CCDD00");
		xpm_data[4] = ft_strdup("b c #BB00BB");
	}

	for (int y = 5; y < (GAME_HEIGHT + 2); y++)
	{
		if (y < (GAME_HEIGHT / 4))
		{
			char *line;
			int i;
			line = malloc(GAME_WIDTH + 1);
			for (i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					line[i] = ',';
				else if (i < (GAME_WIDTH / 4))
					line[i] = 'b';
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH / 2))
					line[i] = '.';
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					line[i] = ',';
				else
					line[i] = '.';
			}
			line[i] = '\0';
			xpm_data[y] = line;
		}
		else if (y < (GAME_HEIGHT / 2))
		{
			char *line;
			int i;
			line = malloc(GAME_WIDTH + 1);
			for (i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					line[i] = '.';
				else if (i < (GAME_WIDTH / 4))
					line[i] = 'a';
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH / 2))
					line[i] = ',';
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					line[i] = '.';
				else
					line[i] = ',';
			}
			line[i] = '\0';
			xpm_data[y] = line;
		}
		else if (y < (GAME_HEIGHT - (GAME_HEIGHT / 4)))
		{
			char *line;
			int i;
			line = malloc(GAME_WIDTH + 1);
			for (i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					line[i] = ',';
				else if (i < (GAME_WIDTH / 4))
					line[i] = 'b';
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH / 2))
					line[i] = '.';
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					line[i] = ',';
				else
					line[i] = '.';
			}
			line[i] = '\0';
			xpm_data[y] = line;
		}
		else
		{
			char *line;
			int i;
			line = malloc(GAME_WIDTH + 1);
			for (i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					line[i] = '.';
				else if (i < (GAME_WIDTH / 4))
					line[i] = 'a';
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH / 2))
					line[i] = ',';
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					line[i] = 'a';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					line[i] = 'b';
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					line[i] = '.';
				else
					line[i] = ',';
			}
			line[i] = '\0';
			xpm_data[y] = line;
		}
	}

	image = mlx_xpm_to_image(view->mlx, xpm_data, &width, &height);
	if (image)
	{
		mlx_put_image_to_window(view->mlx, view->mlx_win, image, 0, 0);
		t = clock() - t;
		double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
		printf("%f secs (%.0f fps) - XPM\n", time_taken, (float)1 / time_taken);
	}
	else
		printf("Image not created\n");
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_image_1(t_data img)
{
	for (int y = 0; y < (GAME_HEIGHT); y++)
	{
		if (y < (GAME_HEIGHT / 4))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else
					my_mlx_pixel_put(&img, i, y, BLUE);
			}
		}
		else if (y < (GAME_HEIGHT / 2))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else
					my_mlx_pixel_put(&img, i, y, YELLOW);
			}
		}
		else if (y < (GAME_HEIGHT - (GAME_HEIGHT / 4)))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else
					my_mlx_pixel_put(&img, i, y, BLUE);
			}
		}
		else
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else
					my_mlx_pixel_put(&img, i, y, YELLOW);
			}
		}
	}
}

void ft_image_2(t_data img)
{
	for (int y = 0; y < (GAME_HEIGHT); y++)
	{
		if (y < (GAME_HEIGHT / 4))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else
					my_mlx_pixel_put(&img, i, y, YELLOW);
			}
		}
		else if (y < (GAME_HEIGHT / 2))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else
					my_mlx_pixel_put(&img, i, y, BLUE);
			}
		}
		else if (y < (GAME_HEIGHT - (GAME_HEIGHT / 4)))
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else
					my_mlx_pixel_put(&img, i, y, YELLOW);
			}
		}
		else
		{
			for (int i = 0; i < GAME_WIDTH; i++)
			{
				if (i < (GAME_WIDTH / 8))
					my_mlx_pixel_put(&img, i, y, RED);
				else if (i < (GAME_WIDTH / 4))
					my_mlx_pixel_put(&img, i, y, BLUE);
				else if (i < ((GAME_WIDTH / 2) - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH / 2))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < ((GAME_WIDTH / 2) + (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, GREEN);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 4)))
					my_mlx_pixel_put(&img, i, y, YELLOW);
				else if (i < (GAME_WIDTH - (GAME_WIDTH / 8)))
					my_mlx_pixel_put(&img, i, y, RED);
				else
					my_mlx_pixel_put(&img, i, y, BLUE);
			}
		}
	}
}

void ft_pixel_put_poc(t_view *view, int ver)
{
	t_data img;

	img.img = mlx_new_image(view->mlx, GAME_WIDTH, GAME_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	if (ver == 1)
		ft_image_1(img);
	else
		ft_image_2(img);
	clock_t t;
	t = clock();
	mlx_put_image_to_window(view->mlx, view->mlx_win, img.img, 0, 0);
	t = clock() - t;
	double time_taken = ((double)t) / CLOCKS_PER_SEC; // calculate the elapsed time
	printf("%f secs (%.0f fps) - Pixel put\n", time_taken, (float)1 / time_taken);
}

void ft_view_events(t_view *view)
{
	mlx_key_hook(view->mlx_win, ft_keyboard_events, view);
	mlx_hook(view->mlx_win, ON_DESTROY, 0, ft_close_window, view);
}

int ft_close_window(t_view *view)
{
	mlx_destroy_window(view->mlx, view->mlx_win);
	free(view->title);
	exit(0);
}

int ft_keyboard_events(int key, t_view *view)
{
	static int counter = 0;
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(view);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX) || (key == W_KEY_MAC || key == UP_ARR_MAC))
	{
		if (counter < 10)
			ft_xpm_data_poc(view, 1);
		else
			ft_pixel_put_poc(view, 1);
	}
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX) || (key == A_KEY_MAC || key == LEFT_ARR_MAC))
	{
		if (counter < 10)
			ft_xpm_data_poc(view, 1);
		else
			ft_pixel_put_poc(view, 1);
	}
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX) || (key == S_KEY_LINUX || key == DOWN_ARR_MAC))
	{
		if (counter < 10)
			ft_xpm_data_poc(view, 2);
		else
			ft_pixel_put_poc(view, 2);
	}
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX) || (key == D_KEY_LINUX || key == RIGHT_ARR_MAC))
	{
		if (counter < 10)
			ft_xpm_data_poc(view, 2);
		else
			ft_pixel_put_poc(view, 2);
	}
	counter++;
	if (counter == 20)
		exit(1);
	return (1);
}
