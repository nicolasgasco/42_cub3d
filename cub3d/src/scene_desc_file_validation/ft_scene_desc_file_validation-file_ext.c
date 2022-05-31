#include "../cub3d.h"
#include "../../Libft/libft.h"

void ft_file_extension_validation(char *file_path)
{
	int		EXT_LEN;
	int		ext_start;
	char	*file_path_ext;

	EXT_LEN = 4;
	ext_start = ft_strlen(file_path) - EXT_LEN;
	if (ext_start == 0)
	{
		ft_putendl_fd("Error: invalid extension", STDERR_FILENO);
		exit(2);
	}
	file_path_ext = ft_substr(file_path, ext_start, EXT_LEN);
	if (ft_strncmp(file_path_ext, ".cub", EXT_LEN) != 0)
	{
		free(file_path_ext);
		ft_putendl_fd("Error: invalid extension", STDERR_FILENO);
		exit(2);
	}
	free(file_path_ext);
}