/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsolinis <jsolinis@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 23:29:00 by jsolinis          #+#    #+#             */
/*   Updated: 2022/05/18 23:30:22 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

/* Struct for map data  */
typedef struct s_map
{
	char	*no_path;
	char	*so_path;
	char	*ea_path;
	char	*we_path;
	char	*f_color;
	char	*c_color;
	int		player_y;
	int		player_x;
	char	player_orientation;
	int		height;
	int		width;
	char	**map_content;
}			t_map;

/* Utils */
// Utils - Common error
void	ft_malloc_error(void);
void	ft_open_file_error(void);
// Utils - Debug
void	ft_write_debug_msg(char *msg);
// Utils - Free
void	ft_free_allocated_map_data(t_map *map);
void	ft_print_error_exit(t_map *map, char *msg, int err);
// Utils - Common utils
int		ft_open_file(char *file_path);
int		ft_isspace(char c);
void	ft_skip_to_non_space_char(char *line, int *iterator);
char	*ft_substr_no_leaks(char *s, unsigned int start, size_t len);
char	*ft_strtrim_no_leaks(char *s1, const char *set);
int		ft_str_is_numeric(char *str);
void	ft_skip_to_content(char *line, int *iterator);
// Utils - Get next line
char	*get_next_line(int fd);
// Utils - Map content
int		ft_is_player_char(char c);
int		ft_is_valid_map_char(char c);
void	ft_check_player_number(t_map *map, int player);
void	ft_set_player_data(t_map *map, int *iterator, int *j, char c);
int		ft_isspace_no_endl(char c);
// Utils - Map
int		ft_is_map_start(char *line);
void	ft_get_map_width(char *line, t_map *map);
char	*ft_skip_to_map_start(char *line, int fd);
void	ft_skip_to_non_space_char_backwards(char *line, int *iterator);
char	*ft_check_to_eof(char *line, int fd, t_map *map);

/* Scene desc validation errors */
void	ft_invalid_extension_error_exit(void);
void	ft_invalid_id_error_exit(t_map *map, char *line);
void	ft_empty_scene_file_error_exit(void);
void	ft_missing_file_path_error_exit(char *o_path_id, char *line,
			t_map *map);
void	ft_invalid_color_code_error_exit(t_map *map, char *line,
			char *col_code_str);
void	ft_invalid_col_statement_error_exit(t_map *map, char *line);
void	ft_incomplete_scene_info_error_exit(t_map *map);
void	ft_duplicate_scene_info_error_exit(t_map *map);
void	ft_invalid_orientation_path_error_exit(char *line,
			char *o_path_id, char *o_path);

/* Scene description file validation */
void	ft_scene_desc_file_validation(int argc, char *file_path, t_map *map);
void	ft_check_num_args(int argc);
void	ft_file_extension_validation(char *file_path);
// Type ids
void	ft_type_ids_validation(char *file_path, t_map *map);
int		ft_validate_scene_file_line(char *line, t_map *map);
// Type ids - Orientation paths
void	ft_validate_parse_o_path(char *line, int *i, t_map *map);
char	*ft_validate_o_path(t_map *map, char *o_path_id, char *line, int *i);
char	*ft_parse_valid_path(t_map *map, char *o_path_id, char *line, int *i);
int		ft_calc_path_length(char *line, int i);
int		ft_check_o_path_already_assigned(t_map *map, char *o_path_id);
int		ft_validate_f_path(t_map *map, char *o_path, char *line, char *o_p_id);
// Type ids - Colors validation
void	ft_validate_parse_color(char *line, int *i, t_map *map);
char	*ft_validate_color_codes(char *line, int *i, t_map *map);
int		ft_parse_color_codes(char *line, int *iterator, t_map *map);
int		ft_parse_single_color_code(t_map *map, char *line, int *iterator);
void	ft_validate_single_col_code(t_map *map, char *col_code_str, char *line);
void	ft_check_col_already_assigned(t_map *map, char *color_id, char *line);
int		ft_check_if_other_num_same_line(char *line, int iterator);
// Type ids - Completeness check
void	ft_type_ids_completeness_check(t_map *map);
void	ft_completeness_check_colors(t_map *map);
void	ft_completeness_check_o_paths(t_map *map);
void	ft_check_o_paths_duplicates(t_map *map);
void	ft_find_o_paths_duplicates(char **path_arr, t_map *map);
// Map content
void	ft_map_content_validation(char *file_path, t_map *map);
void	ft_check_characters(t_map *map);
void	ft_validate_size(t_map *map);
void	ft_validate_walls(t_map *map);
void	ft_validate_content(t_map *map);

#endif
