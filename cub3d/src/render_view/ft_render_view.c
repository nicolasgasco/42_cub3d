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
		printf("%f seconds to render image\n", time_taken);
	}
	else
		printf("Image not created\n");
}

void ft_pixel_put_poc(t_view *view)
{
	if (view)
	{
		// Continue
	}
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
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(view);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX) || (key == W_KEY_MAC || key == UP_ARR_MAC))
	{
		ft_xpm_data_poc(view, 1);
	}
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX) || (key == A_KEY_MAC || key == LEFT_ARR_MAC))
	{
		ft_xpm_data_poc(view, 1);
	}
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX)
		|| (key == S_KEY_LINUX || key == DOWN_ARR_MAC))
	{
		ft_xpm_data_poc(view, 2);
	}
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX) || (key == D_KEY_LINUX || key == RIGHT_ARR_MAC))
	{
		ft_xpm_data_poc(view, 2);
	}
	return (1);
}
