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
# include "../mlx/mlx.h"

/* Game params */
# define GAME_TITLE "Cub3d - Brawl Stars"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define PLAY_WIDTH	900
# define PLAY_HEIGHT 460
# define TEXTURE_SIZE 128

/* Events */
# define ON_DESTROY 17

/* Key bindings */
// Linux
# define ESC_KEY_LINUX 65307
# define LEFT_ARR_LINUX 65361
# define UP_ARR_LINUX 65362
# define RIGHT_ARR_LINUX 65363
# define DOWN_ARR_LINUX 65364
# define A_KEY_LINUX 97
# define W_KEY_LINUX 119
# define D_KEY_LINUX 100
# define S_KEY_LINUX 115

// Mac
# define ESC_KEY_MAC 53
# define LEFT_ARR_MAC 123
# define UP_ARR_MAC 126
# define RIGHT_ARR_MAC 124
# define DOWN_ARR_MAC 125
# define A_KEY_MAC 0
# define W_KEY_MAC 13
# define D_KEY_MAC 2
# define S_KEY_MAC 1

// Conversion
# define DIFF_TO_NUM 55
# define NO_TRANSPARENCY 0

# define PI 3.14159265359
# define PROJ_PLANE_WIDTH 320
# define PROJ_PLANE_HEIGHT 200
# define CUBE_SIZE 64
# define FIELD_OF_VIEW 60.0

/*Vector Struct*/
typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

/* Struct for ray calculation */
typedef struct s_projection
{
	char		player_orientation;
	double		view_angle;
	double		distance_to_pp;
	double		distance_to_wall;
	double		angle_btw_rays;
	t_vector	*player;
	t_vector	*rc_horizontal;
	t_vector	*rc_vertical;
	t_vector	*wall_to_render;
}				t_projection;

/* Struct for each column */
typedef struct s_slice
{
	int		column;
	int		height;
	char	*texture;
	int		wall_x;
}			t_slice;

/* Linked list used to manipulate texture files */
struct s_cinfo
{
	char			col_char;
	int				col_int;
	struct s_cinfo	*next;
};

/* Struct with info on single texture */
typedef struct s_tdata
{
	int				texture_w;
	int				texture_h;
	int				**texture_columns;
	struct s_cinfo	*col_info_list;
}		t_tdata;

/* Struct with info necessary to render textures */
typedef struct s_rdata
{
	int				c_col_int;
	int				f_col_int;
	t_tdata			*textures;
}		t_rdata;

/* Struct for map data  */
typedef struct s_map
{
	int				column;
	char			*no_path;
	char			*so_path;
	char			*ea_path;
	char			*we_path;
	char			*f_color;
	char			*c_color;
	int				height;
	int				width;
	char			**map_content;
	t_projection	*prj;
	t_slice			*slc;
}					t_map;

/* Struct for mlx */
typedef struct s_view
{
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	char	*title;
}			t_view;

/* Utils */
// Utils - Common error
void	ft_malloc_error(void);
void	ft_open_file_error(void);
// Utils - Debug
void	ft_write_debug_msg(char *msg);
void	ft_write_debug_msg_int(char *msg, int int_arg);
// Utils - Free
void	ft_free_allocated_map_data(t_map *map);
void	ft_print_error_exit(t_map *map, char *msg, int err);
void	ft_free_raycast_data(t_map *map);
void	ft_free_slice_data(t_map *map);
// Utils - Common utils
int		ft_open_file(char *file_path);
int		ft_isspace(char c);
void	ft_skip_to_non_space_char(char *line, int *iterator);
char	*ft_substr_no_leaks(char *s, unsigned int start, size_t len);
char	*ft_strtrim_no_leaks(char *s1, const char *set);
int		ft_str_is_numeric(char *str);
void	ft_skip_to_content(char *line, int *iterator);
int		ft_str_contains_char(char *str, char c);
// Utils - Get next line
char	*get_next_line(int fd);
// Utils - Map content
int		ft_is_player_char(char c);
int		ft_is_valid_map_char(char c);
void	ft_check_player_number(t_map *map, int player);
int		ft_isspace_no_endl(char c);
// Utils - Map
int		ft_is_map_start(char *line);
void	ft_get_map_width(char *line, t_map *map);
char	*ft_skip_to_map_start(char *line, int fd);
void	ft_skip_to_non_space_char_backwards(char *line, int *iterator);
char	*ft_check_to_eof(char *line, int fd, t_map *map);
// Utils - Raycast
void	ft_set_player_data(t_map *map, int *iterator, int *j, char c);
double	ft_set_viewing_angle(char c);
void	ft_convert_to_cube_position(t_map *map);
void	ft_set_rc_structure(t_map *map);
void	ft_set_coords_angle_direction_horizontal(t_map *map);
void	ft_set_coords_angle_direction_vertical(t_map *map);
void	ft_set_wall_to_render(t_map *map, double dh, double dv);
double	ft_calculate_angle(t_map *map);

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

/* Raycasting Calculation */
void	ft_raycasting_calculation(t_map *map);
void	ft_raycast_to_slice(t_map *map);

/* Render view */
void	ft_render_view(t_view *view, t_rdata *rdata);
void	ft_view_events(t_view *view);
int		ft_close_window(t_view *view);
int		ft_keyboard_events(int key, t_view *view);

/* Post validation data manip */
void	ft_post_validation_data_manip(t_map *map, t_rdata *rdata);
/* Post validation data manip - Colors */
int		ft_rgb_str_to_int(char *col_str);
void	ft_populate_rgb_int_arr(char *col_str, int *rgb);
int		ft_substr_and_atoi(char *col_str, int start, int end);
int		ft_rgb_to_int(int t, int r, int g, int b);
/* Post validation data manip - Textures */
t_tdata			ft_texture_file_to_columns(char *texture_path);
void			ft_parse_asset_sizes(char *line, t_tdata *texture);
int				ft_calc_size_len(char *line, int i);
void			ft_parse_char_col(char *line, t_tdata *rdata);
struct s_cinfo	*ft_create_col_info_struct(char *line);
int				ft_hex_str_to_int(char *hex);
void			ft_fill_int_matrix_line(t_tdata *texture, char *line, int y);
void			$ft_print_pixel_matrix(t_tdata *texture);
void			$ft_print_col_info_struct(struct s_cinfo *col_info);

// Test
void			ft_render_texture(t_view *view, t_tdata *texture, int x, int y);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
