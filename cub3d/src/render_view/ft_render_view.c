#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_render_view(t_view *view)
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

void	ft_view_events(t_view *view)
{
	mlx_key_hook(view->mlx_win, ft_keyboard_events, view);
	mlx_hook(view->mlx_win, ON_DESTROY, 0, ft_close_window, view);
}

int	ft_close_window(t_view *view)
{
	mlx_destroy_window(view->mlx, view->mlx_win);
	free(view->title);
	exit (0);
}

int	ft_keyboard_events(int key, t_view *view)
{
	if (key == ESC_KEY_LINUX || key == ESC_KEY_MAC)
		ft_close_window(view);
	else if ((key == W_KEY_LINUX || key == UP_ARR_LINUX)
		|| (key == W_KEY_MAC || key == UP_ARR_MAC))
	{
		printf("Arrow up or W\n");
	}
	else if ((key == A_KEY_LINUX || key == LEFT_ARR_LINUX)
		|| (key == A_KEY_MAC || key == LEFT_ARR_MAC))
	{
		printf("Arrow left or a\n");
	}
	else if ((key == S_KEY_LINUX || key == DOWN_ARR_LINUX)
		|| (key == S_KEY_LINUX || key == DOWN_ARR_MAC))
	{
		printf("Arrow down or S\n");
	}
	else if ((key == D_KEY_LINUX || key == RIGHT_ARR_LINUX)
		|| (key == D_KEY_LINUX || key == RIGHT_ARR_MAC))
	{
		printf("Arrow right or D\n");
	}
	return (1);
}