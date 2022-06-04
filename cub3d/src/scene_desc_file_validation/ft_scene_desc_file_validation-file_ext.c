#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_file_extension_validation(char *file_path)
{
	int		ext_len;
	int		ext_start;
	char	*file_path_ext;

	ext_len = 4;
	ext_start = ft_strlen(file_path) - ext_len;
	if (ext_start == 0)
	{
		ft_putendl_fd("Error: invalid extension", STDERR_FILENO);
		exit(2);
	}
	file_path_ext = ft_substr(file_path, ext_start, ext_len);
	if (ft_strncmp(file_path_ext, ".cub", ext_len) != 0)
	{
		free(file_path_ext);
		ft_putendl_fd("Error: invalid extension", STDERR_FILENO);
		exit(2);
	}
	free(file_path_ext);
}
