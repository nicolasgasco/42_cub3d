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
    int        height;
    int        width;
    char       **map_content;
}            t_map;

/* Utils */
int     ft_open_file(char *file_path);
int     ft_isspace(char c);
void    ft_skip_to_non_space_char(char *line, int *iterator);
char	*get_next_line(int fd);
char    *ft_substr_no_leaks(char *s, unsigned int start, size_t len);
char    *ft_strtrim_no_leaks(char *s1, const char *set);
int     ft_str_is_numeric(char *str);

/* Common errors */
void    ft_malloc_error(void);
void    ft_open_file_error(void);

/* Scene description file validation */
void    ft_check_num_args(int argc);
void    ft_scene_desc_file_validation(char *file_path, t_map *map);
void    ft_file_extension_validation(char *file_path);
void    ft_type_ids_validation(char *file_path);
int    ft_open_scene_file(char *file_path);
int     ft_validate_scene_file_line(char *line);
void    ft_parse_orientation_path(char *line, int *i);
void    ft_validate_orientation_path(char *o_path_acronym, char *line, int *i);
int     ft_calc_path_length(char *line, int i);
int     ft_open_file_path_validation(char *o_path, char *line, char *o_path_acronym);
void    ft_parse_colors(char *line, int *i);
void    ft_validate_colors(char *color_char, char *line, int *i);
int     ft_parse_color_codes(char *line, int *i);
void    ft_validate_color_code_str(char *color_code_str, char *line);
int     ft_parse_single_color_code(char *line, int *iterator);
void    ft_map_content_validation(char *file_path, t_map *map);

#endif
