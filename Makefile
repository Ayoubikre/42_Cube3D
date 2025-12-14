#----------------------------------   Platform detection :

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_LIBRARIES = Tools/mlx/linux/libmlx42_linux.a \
			-ldl -lglfw -lm -lpthread

	add = echo "" && \
	GTK_DEBUG=none ./$(NAME) map.cub 2> >(grep -vi 'gtk-warning' >&2)

	b_add = echo "" && \
	GTK_DEBUG=none ./$(B_NAME) map.cub 2> >(grep -vi 'gtk-warning' >&2)

else
	MLX_LIBRARIES = Tools/mlx/macOS/libmlx42_combined.a \
		-framework Cocoa -framework OpenGL -framework IOKit -lm -ldl

	add = echo "" && ./$(NAME) map.cub
	b_add = echo "" && ./$(B_NAME) map.cub
endif

#---------------------------------------------------------------#

CC = cc

CFLAGS  = -Wall -Werror -Wextra
# CFLAGS  = -Wall -Werror -Wextra -fsanitize=address -g

SRC = Mandatory/main.c \
		Mandatory/Parsing/utils.c \
		Mandatory/Parsing/parsing.c \
		Mandatory/Parsing/parsing_utils.c \
		Mandatory/Parsing/parse_levels.c \
		Mandatory/Parsing/textures.c \
		Mandatory/Parsing/color.c \
		Mandatory/Parsing/color_utils.c \
		Mandatory/Parsing/map.c \
		Mandatory/Parsing/map_utils.c \
		Mandatory/Parsing/map_utils2.c \
		Mandatory/Game/ft_wrap_start_game.c \
		Mandatory/Game/ft_wrap_main_core.c \
		Mandatory/Game/ft_init.c \
		Mandatory/Game/ft_raycast.c \
		Mandatory/Game/ft_player.c \
		Mandatory/Game/ft_player2.c \
		Mandatory/Game/ft_keys.c \
		Mandatory/Game/ft_list.c \
		Mandatory/Game/ft_lvls.c \
		Mandatory/Game/ft_minimap.c \
		Mandatory/Game/ft_animation.c \
		Mandatory/Game/ft_utils.c \
		Mandatory/Game/ft_free.c \
		Mandatory/Randering/ft_3drendering.c \
		Mandatory/Randering/ft_textures.c \
		Mandatory/Randering/render_text.c \
		Mandatory/Randering/redering_text_utils.c

OBJ = $(SRC:.c=.o)

Head = Mandatory/includes/cub3d.h Mandatory/includes/Data.h

libft_DIR = ./Mandatory/42_Libft
libft = $(libft_DIR)/libft.a

NAME = cub3D


B_SRC = Bonus/main_bonus.c \
		Bonus/Parsing/utils_bonus.c \
		Bonus/Parsing/parsing_bonus.c \
		Bonus/Parsing/parsing_utils_bonus.c \
		Bonus/Parsing/parse_levels_bonus.c \
		Bonus/Parsing/textures_bonus.c \
		Bonus/Parsing/color_bonus.c \
		Bonus/Parsing/color_utils_bonus.c \
		Bonus/Parsing/map_bonus.c \
		Bonus/Parsing/map_utils_bonus.c \
		Bonus/Parsing/map_utils2_bonus.c \
		Bonus/Game/ft_wrap_start_game_bonus.c \
		Bonus/Game/ft_wrap_main_core_bonus.c \
		Bonus/Game/ft_init_bonus.c \
		Bonus/Game/ft_raycast_bonus.c \
		Bonus/Game/ft_player_bonus.c \
		Bonus/Game/ft_player2_bonus.c \
		Bonus/Game/ft_keys_bonus.c \
		Bonus/Game/ft_list_bonus.c \
		Bonus/Game/ft_lvls_bonus.c \
		Bonus/Game/ft_minimap_bonus.c \
		Bonus/Game/ft_animation_bonus.c \
		Bonus/Game/ft_utils_bonus.c \
		Bonus/Game/ft_free_bonus.c \
		Bonus/Randering/ft_3drendering_bonus.c \
		Bonus/Randering/ft_textures_bonus.c \
		Bonus/Randering/render_text_bonus.c \
		Bonus/Randering/redering_text_utils_bonus.c

B_OBJ = $(B_SRC:.c=.o)

B_Head = bonus/includes/cub3d_bonus.h bonus/includes/Data_bonus.h

libft_DIR_B = ./Bonus/42_Libft
libft_B = $(libft_DIR_B)/libft.a

B_NAME = cub3D_bonus



all: clean $(NAME)

$(NAME): $(OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBRARIES) $(libft) -o $(NAME)
	make clean
	$(add)

Mandatory/%.o: Mandatory/%.c $(Head) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: clean $(B_NAME)

$(B_NAME): $(B_OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(B_OBJ) $(MLX_LIBRARIES) $(libft_B) -o $(B_NAME)
	make clean
	$(b_add)

bonus/%.o: Bonus/%.c $(B_Head) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	@make -C $(libft_DIR) clean
#	@make -C $(libft_DIR_B) clean
	@rm -f $(OBJ)
	@rm -f $(B_OBJ)

fclean: clean
#	@make -C $(libft_DIR) fclean
#	@make -C $(libft_DIR_B) fclean
	@rm -f $(NAME)
	@rm -f $(B_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
