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

# CFLAGS  = -Wall
# CFLAGS  = -Wall -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra


SRC = Mandatory/main.c \
		Mandatory/Rays/ft_remove_later.c \
		Mandatory/parsing/utils.c \
		Mandatory/parsing/parsing.c \
		Mandatory/parsing/parsing_utils.c \
		Mandatory/parsing/parse_levels.c \
		Mandatory/parsing/textures.c \
		Mandatory/parsing/color.c \
		Mandatory/parsing/color_utils.c \
		Mandatory/parsing/map.c \
		Mandatory/parsing/map_utils.c \
		Mandatory/parsing/map_utils2.c \
		Mandatory/Rays/ft_wrap_start_game.c \
		Mandatory/Rays/ft_wrap_main_core.c \
		Mandatory/Rays/ft_init.c \
		Mandatory/Rays/ft_raycast.c \
		Mandatory/Rays/ft_player.c \
		Mandatory/Rays/ft_player2.c \
		Mandatory/Rays/ft_keys.c \
		Mandatory/Rays/ft_list.c \
		Mandatory/Rays/ft_lvls.c \
		Mandatory/Rays/ft_minimap.c \
		Mandatory/Rays/ft_animation.c \
		Mandatory/Rays/ft_utils.c \
		Mandatory/Rays/ft_free.c \
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
		Bonus/Rays/ft_remove_later_bonus.c \
		Bonus/parsing/utils_bonus.c \
		Bonus/parsing/parsing_bonus.c \
		Bonus/parsing/parsing_utils_bonus.c \
		Bonus/parsing/parse_levels_bonus.c \
		Bonus/parsing/textures_bonus.c \
		Bonus/parsing/color_bonus.c \
		Bonus/parsing/color_utils_bonus.c \
		Bonus/parsing/map_bonus.c \
		Bonus/parsing/map_utils_bonus.c \
		Bonus/parsing/map_utils2_bonus.c \
		Bonus/Rays/ft_wrap_start_game_bonus.c \
		Bonus/Rays/ft_wrap_main_core_bonus.c \
		Bonus/Rays/ft_init_bonus.c \
		Bonus/Rays/ft_raycast_bonus.c \
		Bonus/Rays/ft_player_bonus.c \
		Bonus/Rays/ft_player2_bonus.c \
		Bonus/Rays/ft_keys_bonus.c \
		Bonus/Rays/ft_list_bonus.c \
		Bonus/Rays/ft_lvls_bonus.c \
		Bonus/Rays/ft_minimap_bonus.c \
		Bonus/Rays/ft_animation_bonus.c \
		Bonus/Rays/ft_utils_bonus.c \
		Bonus/Rays/ft_free_bonus.c \
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
	$(add)

Mandatory/%.o: Mandatory/%.c $(Head) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: clean $(B_NAME)

$(B_NAME): $(B_OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(B_OBJ) $(MLX_LIBRARIES) $(libft_B) -o $(B_NAME)
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
