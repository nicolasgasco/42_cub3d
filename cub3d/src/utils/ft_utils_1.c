#include "../cub3d.h"
#include "../../Libft/libft.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_skip_to_content(char *line, int *iterator)
{
	if (line)
	{
		while (line[*iterator])
		{
			if (ft_isspace_no_endl(line[*iterator]))
				*iterator += 1;
			else
				return ;
		}
	}
}
