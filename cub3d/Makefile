NAME = cub3d
FLAGS = -Wall -Wextra -Werror
SANITIZE = -g3 -fsanitize=address
VALGRIND = -g -Og -std=gnu99
INC = -I%.h -I$(LIB_DIR)%.h
MINILIB_LINUX= -Lmlx -lmlx_Linux -lXext -lX11 -lm -lz
MINILIB_MAC = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRC_NAME =	cub3d.c\
		scene_desc_file_validation/ft_scene_desc_file_validation.c\
		scene_desc_file_validation/ft_type_ids_validation.c\
		scene_desc_file_validation/ft_type_ids_validation-orientation.c\
		scene_desc_file_validation/ft_type_ids_validation-orientation_utils.c\
		scene_desc_file_validation/ft_type_ids_validation-colors.c\
		scene_desc_file_validation/ft_type_ids_validation-colors_utils.c\
		scene_desc_file_validation/ft_type_ids_validation-completeness.c\
		scene_desc_file_validation/ft_map_content_validation.c\
		scene_desc_file_validation/ft_map_content_validation-map_size.c\
		scene_desc_file_validation/ft_map_content_validation-allowed_chars.c\
		scene_desc_file_validation/ft_map_content_validation-map_walls.c\
		scene_desc_file_validation/ft_map_content_validation-map_content.c\
		scene_desc_file_validation/ft_type_ids_validation-errors_0.c\
		scene_desc_file_validation/ft_type_ids_validation-errors_1.c\
		render_window/ft_render_view.c\
		utils/get_next_line.c\
		utils/ft_utils_0.c\
		utils/ft_utils_1.c\
		utils/ft_map_utils.c\
		utils/ft_map_content_utils.c\
		utils/ft_common_errs.c\
		utils/ft_free.c\
		utils/ft_debug.c\

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = ./Libft/
SRC_DIR = ./src/
SCN_DIR = scene_desc_file_validation/
WIN_DIR = render_window/
UTL_DIR = utils/
OBJ_DIR = ./obj/
MLX_DIR = ./mlx/
MLX_LINUX_DIR = ./minilibx-linux/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@make -C $(MLX_LINUX_DIR) --silent
	@gcc $(FLAGS) $(SANITIZE) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft $(MINILIB_LINUX)
	@echo "##### cub3d compiling finished! #####"

mac: $(OBJ)
	@make -C $(LIB_DIR) --silent
	@make -C $(MLX_DIR) --silent
	@gcc $(FLAGS) $(SANITIZE) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft $(MINILIB_MAC)
	@echo "##### cub3d compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)$(SCN_DIR)
	@mkdir -p $(OBJ_DIR)$(UTL_DIR)
	@mkdir -p $(OBJ_DIR)$(WIN_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) $(SANITIZE) -o $@ -c $< $(INC)

clean:
	@make -C $(LIB_DIR) clean  --silent
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "##### Removed object files #####"

fclean: clean
	@make -C $(LIB_DIR) fclean  --silent
	@rm -f $(NAME)
	@echo "##### Removed binary files #####"

re: fclean all

test_validation:
	@make re > /dev/null 2> /dev/null
	@sh tests/validation_tests.sh

.PHONY: all clean fclean re test mac
