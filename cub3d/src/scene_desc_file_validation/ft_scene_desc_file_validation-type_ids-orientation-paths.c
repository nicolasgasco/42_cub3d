#include "../cub3d.h"
#include "../../Libft/libft.h"

void    ft_parse_orientation_path(char *line, int *i)
{
    char *o_path_acronym;

    o_path_acronym = ft_substr(line, *i, 2);
    *i = *i + 2;
    if (ft_strncmp(o_path_acronym, "NO", 2) == 0)
        ft_validate_orientation_path(o_path_acronym, line, i);
    else if (ft_strncmp(o_path_acronym, "SO", 2) == 0)
        ft_validate_orientation_path(o_path_acronym, line, i);
    else if (ft_strncmp(o_path_acronym, "WE", 2) == 0)
        ft_validate_orientation_path(o_path_acronym, line, i);
    else if (ft_strncmp(o_path_acronym, "EA", 2) == 0)
        ft_validate_orientation_path(o_path_acronym, line, i);
    else
    {
        ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
        free(line);
        free(o_path_acronym);
        exit(5);
    }
    free(o_path_acronym);
}

void    ft_validate_orientation_path(char *o_path_acronym, char *line, int *i)
{
    char    *o_path_untrimmed;
    char    *o_path;
    int     o_file_fd;

    if (!ft_isspace(line[*i]))
    {
        free(o_path_acronym);
        free(line);
        ft_putendl_fd("Error: invalid identifier", STDERR_FILENO);
        exit(5);
    }
    ft_skip_to_non_space_char(line, i);
    if (line[*i] == '\0')
    {
        free(o_path_acronym);
        free(line);
        ft_putendl_fd("Error: missing file path", STDERR_FILENO);
        exit(7);
    }
    o_path_untrimmed = ft_substr(line, *i, ft_calc_path_length(line, *i));
    o_path = ft_strtrim(o_path_untrimmed, " \n");
    free(o_path_untrimmed);
    o_file_fd = ft_open_file(o_path);
    free(o_path);
    printf("Line is validated ✅\n");
    close(o_file_fd);
}

int ft_calc_path_length(char *line, int i)
{
    int len;

    len = 0;
    while (ft_isspace(line[i]) == 0)
    {
        len++;
        i++;
    }
    return (len);
}

