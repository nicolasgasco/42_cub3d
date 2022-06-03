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

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/* Struct for map data  */
typedef struct s_map
{
    char       *no_path;
    char       *so_path;
    char       *ea_path;
    char       *we_path;
    char       *f_color;
    char       *c_color;
    int        height;
    int        width;
    char       **map_content;
}            t_map;

/* Utils */
int     ft_open_file(char *file_path);
int     ft_isspace(char c);
void    ft_skip_to_non_space_char(char *line, int *iterator);
char	  *get_next_line(int fd);
char    *ft_substr_no_leaks(char *s, unsigned int start, size_t len);
char    *ft_strtrim_no_leaks(char *s1, const char *set);
int     ft_str_is_numeric(char *str);
int     ft_is_map_start(char *line);
void    ft_get_map_width(char *line, t_map *map);
char    *ft_skip_to_map_start(char *line, int fd);
void	  ft_skip_to_non_space_char_backwards(char *line, int *iterator);
void    ft_free_map_struct(t_map *map);
int     ft_is_player_char(char c);
int     ft_is_valid_map_char(char c);
void    ft_free_allocated_map_data(t_map *map);
void    ft_write_debug_msg(char *msg);

/* Common errors */
void    ft_malloc_error(void);
void    ft_open_file_error(void);
void    ft_invalid_id_error_exit(char *line);
void    ft_duplicate_scene_info_error_exit(void);
void    ft_invalid_col_statement_error_exit(char *line);

/* Scene description file validation */
void    ft_check_num_args(int argc);
void    ft_scene_desc_file_validation(char *file_path, t_map *map);
void    ft_file_extension_validation(char *file_path);
void    ft_type_ids_validation(char *file_path, t_map *map);
int     ft_open_scene_file(char *file_path);
int     ft_validate_scene_file_line(char *line, t_map *map);
void    ft_parse_orientation_path(char *line, int *i, t_map *map);
int     ft_check_if_map_o_path_unassigned(t_map *map, char *o_path_acronym);
char    *ft_validate_orientation_path(t_map *map, char *o_path_acronym, char *line, int *i);
int     ft_calc_path_length(char *line, int i);
int     ft_open_file_path_validation(char *o_path, char *line, char *o_path_acronym);
void    ft_parse_colors(char *line, int *i, t_map *map);
char    *ft_validate_colors(char *color_char, char *line, int *i, t_map *map);
int     ft_check_if_other_num_same_line(char *line, int iterator);
int     ft_parse_color_codes(char *line, int *iterator, t_map *map);
void    ft_validate_color_code_str(t_map *map, char *color_code_str, char *line);
int     ft_parse_single_color_code(t_map *map, char *line, int *iterator);
void    ft_map_content_validation(char *file_path, t_map *map);
void	ft_validate_size(t_map *map);
void	ft_validate_walls(t_map *map);
void	ft_validate_content(t_map *map);
void    ft_type_ids_completeness_check(t_map *map);
void    ft_completeness_check_colors(t_map *map);
void    ft_completeness_check_o_paths(t_map *map);
void    ft_check_o_paths_duplicates(t_map *map);
void    ft_find_o_paths_duplicates(char **path_arr, t_map *map);

#endif
