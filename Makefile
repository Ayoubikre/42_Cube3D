#----------------------------------   Platform detection :

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_LIBRARIES = Tools/mlx/linux/libmlx42_linux.a \
			-ldl -lglfw -lm -lpthread

	add = echo "" && \
	GTK_DEBUG=none ./$(NAME) ./Tools/maps/level1.cub 2> >(grep -vi 'gtk-warning' >&2)

else
	MLX_LIBRARIES = Tools/mlx/macOS/libmlx42_combined.a \
		-framework Cocoa -framework OpenGL -framework IOKit -lm -ldl

	add = echo "" && ./$(NAME) Tools/maps/level1.cub
endif

#---------------------------------------------------------------#

CC = cc

CFLAGS  = -Wall -Werror -Wextra

SRC = main.c \
		Parsing/utils.c \
		Parsing/parsing.c \
		Parsing/parsing_utils.c \
		Parsing/parse_levels.c \
		Parsing/textures.c \
		Parsing/color.c \
		Parsing/color_utils.c \
		Parsing/map.c \
		Parsing/map_utils.c \
		Parsing/map_utils2.c \
		Game/ft_wrap_start_game.c \
		Game/ft_wrap_main_core.c \
		Game/ft_init.c \
		Game/ft_init_2.c \
		Game/ft_raycast.c \
		Game/ft_player.c \
		Game/ft_player2.c \
		Game/ft_keys.c \
		Game/ft_list.c \
		Game/ft_lvls.c \
		Game/ft_minimap.c \
		Game/ft_map.c \
		Game/ft_animation.c \
		Game/ft_animation2.c \
		Game/ft_hands.c \
		Game/ft_utils.c \
		Game/ft_free.c \
		Randering/ft_3drendering.c \
		Randering/ft_textures.c \
		Randering/render_text.c \
		Randering/redering_text_utils.c

OBJ = $(SRC:.c=.o)

Head = includes/cub3d.h includes/Data.h

libft_DIR = ./42_Libft
libft = $(libft_DIR)/libft.a

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBRARIES) $(libft) -o $(NAME)
	make clean
	$(add)

%.o: %.c $(Head) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(libft_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(libft_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
