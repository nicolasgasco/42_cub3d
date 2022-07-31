/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngasco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:14:49 by ngasco            #+#    #+#             */
/*   Updated: 2022/07/19 12:33:57 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../../Libft/libft.h"

void	ft_free_allocated_map_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		if (map->map_content[i])
			free(map->map_content[i]);
		i++;
	}
	if (map->map_content)
		free(map->map_content);
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->we_path)
		free(map->we_path);
	if (map->f_color)
		free(map->f_color);
	if (map->c_color)
		free(map->c_color);
	if (map->slc)
		free(map->slc);
	ft_free_allocated_render_data(map->rdata);
}

void	ft_free_allocated_render_data(t_rdata *rdata)
{
	int				i;
	int				j;
	struct s_cinfo	*curr;
	struct s_cinfo	*temp;

	i = 0;
	j = 0;
	if (!rdata->textures)
	{
		printf("No existe\n");
		return ;
	}
	while (i < 4)
	{
		curr = rdata->textures[i].col_info_list;
		while (curr)
		{
			if (curr->next)
			{
				temp = curr;
				curr = temp->next;
				free(temp);
			}
			else
			{
				free(curr);
				break ;
			}
		}
		j = 0;
		while (j < TEXTURE_SIZE)
		{
			if (rdata->textures[i].texture_columns[j])
				free(rdata->textures[i].texture_columns[j]);
			else
				break ;
			j++;
		}
		free(rdata->textures[i].texture_columns);
		i++;
	}
	free(rdata->textures);
}

void	ft_print_error_exit(t_map *map, char *msg, int err)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	ft_free_allocated_map_data(map);
	exit(err);
}

void	ft_free_raycast_data(t_map *map)
{
	if (map->prj->wall_to_render)
		free(map->prj->wall_to_render);
	if (map->slc)
		free(map->slc);
}
