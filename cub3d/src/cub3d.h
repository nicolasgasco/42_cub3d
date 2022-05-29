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

#include "../gnl/get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_map_data
{
    int	    count;
    int	    max_width;
    char    **content;
}        t_map_data;

/* Utils */
int     ft_open_file(char *file_path);
int     ft_isspace(char c);
void    ft_skip_to_non_space_char(char *line, int *iterator);
int	ft_ismapchar(char c);

/* Common errors */
void    ft_malloc_error(void);
void    ft_open_file_error(void);

/* Scene description file validation */
void    ft_check_num_args(int argc);
void    ft_scene_desc_file_validation(char *file_path, t_map_data *map);
void    ft_file_extension_validation(char *file_path);
void    ft_type_ids_validation(char *file_path, t_map_data *map);
int     ft_open_scene_file(char *file_path);
void    ft_validate_scene_file_line(char *line, t_map_data *map);
void    ft_parse_orientation_path(char *line, int *i);
void    ft_validate_orientation_path(char *o_path_acronym, char *line, int *i);
int     ft_calc_path_length(char *line, int i);
int	ft_map_validation(char *line, t_map_data *map);

#endif
