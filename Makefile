NAME = miniRT

SRC_DIR = sources/

SRC = $(SRC_DIR)main.c\
	$(SRC_DIR)camera.c\
	$(SRC_DIR)collision.c\
	$(SRC_DIR)collision_utils.c\
	$(SRC_DIR)color.c\
	$(SRC_DIR)cylinder.c\
	$(SRC_DIR)data.c\
	$(SRC_DIR)errors.c\
	$(SRC_DIR)file_reader.c\
	$(SRC_DIR)image.c\
	$(SRC_DIR)keyhandler.c\
	$(SRC_DIR)keyhandler2.c\
	$(SRC_DIR)light.c\
	$(SRC_DIR)light_utils.c\
	$(SRC_DIR)mouse.c\
	$(SRC_DIR)object.c\
	$(SRC_DIR)object_array.c\
	$(SRC_DIR)parser.c\
	$(SRC_DIR)plane.c\
	$(SRC_DIR)precalculations.c\
	$(SRC_DIR)printer.c\
	$(SRC_DIR)ray.c\
	$(SRC_DIR)sphere.c\
	$(SRC_DIR)transformation.c\
	$(SRC_DIR)utils.c\
	$(SRC_DIR)validation.c\
	$(SRC_DIR)validation_utils.c\
	$(SRC_DIR)vector.c\
	$(SRC_DIR)vector_math.c\
	$(SRC_DIR)vector_geometry.c


FLAGS = -Wall -Werror -Wextra -O3
OFLAGS += -Iinclude -ldl -lglfw -pthread -lm -march=native -flto
MAKEFLAGS += --no-print-directory
HEADS = -I. $(MLX_HEAD) -I$(LIBFT_DIR)

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
LIBFT_LINK = -L$(LIBFT_DIR) -lft
LIBFT_INC = -I$(LIBFT_DIR)/includes

OBJ_DIR = objects/
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_DIRS = $(sort $(dir $(OBJS)))

MLX = ./MLX42
MLX_HEAD = -I $(MLX)/include
LIBMLX = $(MLX)/build/libmlx42.a

all: $(NAME)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJ_DIRS) $(OBJS)
		@cc $(OBJS) $(LIBFT) $(LIBMLX) $(OFLAGS) -o $(NAME) > /dev/null
		@echo "\n\033[0;32mLet's mini!\033[0m\n"

$(LIBFT):
		@make -C $(LIBFT_DIR)
		@echo "\n\033[0;32mLibft ready\033[0m\n"

$(LIBMLX):
		@if [ ! -d "$(MLX)" ]; then \
			echo "\n\033[0;33mCloning MLX...\033[0m\n"; \
			git clone https://github.com/codam-coding-college/MLX42.git $(MLX) > /dev/null 2>&1; \
		fi
		@if [ ! -d "$(MLX)/build" ]; then \
			cmake $(MLX) -B $(MLX)/build > /dev/null; \
		fi
		@make -C $(MLX)/build -j4 > /dev/null
		@echo "\n\033[0;32mMLX ready\033[0m\n"

$(OBJ_DIRS):
		@mkdir -p $(OBJ_DIRS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
		@cc $(FLAGS) $(LIBFT_INC) -c $< -o $@ $(HEADS)
clean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(MLX)/build
		@make -C $(LIBFT_DIR) clean

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIBFT_DIR) fclean
		@rm -rf $(MLX)
		@echo "\n\033[0;31mAll is gone\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
