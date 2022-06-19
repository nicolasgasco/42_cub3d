/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_desc_file_validation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/06/09 13:14:58 by ngasco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void ft_validate_texture_files(t_map *map)
{
    void *mlx;

    mlx = mlx_init();
    if (!ft_xpm_file_is_valid(map->no_path, mlx))
    {
        printf("NO texture is invalid\n");
        free(mlx);
        exit(1000);
    }
    if (!ft_xpm_file_is_valid(map->ea_path, mlx))
    {
        printf("NO texture is invalid\n");
        free(mlx);
        exit(1000);
    }
    if (!ft_xpm_file_is_valid(map->so_path, mlx))
    {
        printf("NO texture is invalid\n");
        free(mlx);
        exit(1000);
    }
    if (!ft_xpm_file_is_valid(map->we_path, mlx))
    {
        printf("NO texture is invalid\n");
        free(mlx);
        exit(1000);
    }
}

int ft_xpm_file_is_valid(char *path, void *mlx)
{
    void *img;
    int size;

    size = TEXTURE_SIZE;
    img = NULL;
    img = mlx_xpm_file_to_image(mlx, path, &size, &size);
    if (img == NULL)
    {
        printf("Invalid XPM\n");
        free(mlx);
        return (0);
    }
    mlx_destroy_image(mlx, img);
    return (1);
}
