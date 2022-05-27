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

/* Scene description file validation */
void    ft_check_num_args(int argc);
void    ft_scene_desc_file_validation(char *file_path);
void    ft_file_extension_validation(char *file_path);
void    ft_type_ids_validation(char *file_path);

#endif
