#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_validate_orientation_path(char *line, int *i)
{
    char *o_path_acronym;

    o_path_acronym = ft_substr(line, *i, 2);
    if (ft_strncmp(o_path_acronym, "NO", 2) == 0)
    {
        printf("Found NO\n");
    }
    else if (ft_strncmp(o_path_acronym, "SO", 2) == 0)
    {
        printf("Found SO\n");
    }
    else if (ft_strncmp(o_path_acronym, "WE", 2) == 0)
    {
        printf("Found WE\n");
    }
    else if (ft_strncmp(o_path_acronym, "WE", 2) == 0)
    {
        printf("Found EA\n");
    }
    else
    {
        ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
        free(o_path_acronym);
        exit(5);
    }
    free(o_path_acronym);
}
