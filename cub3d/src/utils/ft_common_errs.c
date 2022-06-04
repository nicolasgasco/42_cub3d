#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_malloc_error(void)
{
	ft_putendl_fd("Error: memory error", STDERR_FILENO);
	exit(100);
}

void	ft_open_file_error(void)
{
	ft_putendl_fd("Error: file opening failed", STDERR_FILENO);
	exit(3);
}
