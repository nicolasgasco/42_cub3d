#include "../cub3d.h"
#include "../../Libft/libft.h"

int *ft_texture_file_to_columns(char *texture_path, t_rdata *rdata)
{
	int *result;
	int fd;
	char *line;

	printf("Manipulating texture %s\n", texture_path);
	fd = open(texture_path, O_RDONLY);
	if (fd == -1)
		ft_open_file_error();
	while ((line = get_next_line(fd)))
	{
		if (ft_str_contains_char(line, '#'))
		{
			ft_parse_char_col(line, rdata);
		}
		free(line);
	}
	result = malloc(sizeof(int) * 2);
	result[0] = 1;
	result[1] = 2;
	printf("C is .%c.\n", rdata->col_info_list->col_char);
	printf("C is .%c.\n", rdata->col_info_list->next->col_char);
	printf("C is .%c.\n", rdata->col_info_list->next->next->col_char);
	printf("C is .%c.\n", rdata->col_info_list->next->next->next->col_char);
	printf("C is .%c.\n", rdata->col_info_list->next->next->next->next->col_char);
	return (result);
}

void ft_parse_char_col(char *line, t_rdata *rdata)
{
	struct s_cinfo *curr;

	curr = rdata->col_info_list;
	if (!curr)
	{
		rdata->col_info_list = ft_create_col_info_struct(line);
		return;
	}
	while (curr)
	{
		if (curr->next)
			curr = curr->next;
		else
			break;
	}
	curr->next = ft_create_col_info_struct(line);
}

struct s_cinfo *ft_create_col_info_struct(char *line)
{
	int i;
	char col_char;
	char *col_hex;
	struct s_cinfo *col_info;
	i = 0;
	col_char = '\0';
	col_hex = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			col_char = line[i + 1];
		}
		if (line[i] == '#')
		{
			col_hex = ft_substr(line, i + 1, 6);
			break;
		}
		i++;
	}
	col_info = malloc(sizeof(struct s_cinfo));
	col_info->col_char = col_char;
	if (col_hex)
	{
		// Continue
	}
	col_info->col_int = 10;
	col_info->next = NULL;
	return (col_info);
}