NAME = cub3d
FLAGS = -Wall -Wextra -Werror
SANITIZE = -g -fsanitize=address
VALGRIND = -g -Og -std=gnu99
INC = -I%.h -I$(LIB_DIR)%.h

SRC_NAME =	cub3d.c\
		scene_desc_file_validation/ft_check_num_args.c\
		scene_desc_file_validation/ft_scene_desc_file_validation.c\
		scene_desc_file_validation/ft_scene_desc_file_validation-file_ext.c\
		scene_desc_file_validation/ft_scene_desc_file_validation-type_ids.c\
		scene_desc_file_validation/ft_scene_desc_file_validation-type_ids-orientation-paths.c\
		utils/get_next_line.c\
		utils/ft_utils.c\
		utils/ft_common_errs.c\

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAME))

LIB_DIR = ./Libft/
SRC_DIR = ./src/
SCN_DIR = scene_desc_file_validation/
UTL_DIR = utils/
OBJ_DIR = ./obj/

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR) --silent
	@gcc $(FLAGS) -g -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft
	@echo "##### cub3d compiling finished! #####"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)$(SCN_DIR)
	@mkdir -p $(OBJ_DIR)$(UTL_DIR)
	@echo "##### Creating" [ $@ ] " #####"
	@gcc $(FLAGS) -g -o $@ -c $< $(INC)

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

.PHONY: all clean fclean re
