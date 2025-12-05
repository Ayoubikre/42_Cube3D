
#----------------------------------   Platform detection :

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_LIBRARIES = Tools/mlx/linux/libmlx42_linux.a \
			-ldl -lglfw -lm -lpthread

	add = echo "" && \
	GTK_DEBUG=none ./$(NAME) map.cub 2> >(grep -vi 'gtk-warning' >&2)
else
    MLX_LIBRARIES = Tools/mlx/macOS/libmlx42_combined.a \
        -framework Cocoa -framework OpenGL -framework IOKit -lm -ldl

	add = echo "" && ./$(NAME) map.cub
endif

#---------------------------------------------------------------#

CC = cc

# CFLAGS  = -Wall
# CFLAGS  = -Wall -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra


Parse = mandatory/parsing/utils.c \
		mandatory/parsing/parsing.c \
		mandatory/parsing/parsing_utils.c \
		mandatory/parsing/parse_levels.c \
	  	mandatory/parsing/textures.c \
		mandatory/parsing/color.c \
		mandatory/parsing/color_utils.c \
		mandatory/parsing/map.c \
		mandatory/parsing/map_utils.c \
		mandatory/parsing/map_utils2.c


Game = 	mandatory/Rays/ft_wrap_start_game.c \
		mandatory/Rays/ft_wrap_main_core.c \
		mandatory/Rays/ft_init.c \
		mandatory/Rays/ft_raycast.c \
		mandatory/Rays/ft_player.c \
		mandatory/Rays/ft_player2.c \
		mandatory/Rays/ft_keys.c\
		mandatory/Rays/ft_list.c\
		mandatory/Rays/ft_lvls.c\
		mandatory/Rays/ft_minimap.c\
		mandatory/Rays/ft_animation.c\
		mandatory/Rays/ft_utils.c \
		mandatory/Rays/ft_free.c \
		mandatory/Randering/ft_3drendering.c \
		mandatory/Randering/ft_textures.c \
		mandatory/Randering/render_text.c \
		mandatory/Randering/redering_text_utils.c
		

SRC = 	mandatory/main.c \
		mandatory/Rays/ft_remove_later.c \
		$(Parse)  \
		$(Game)
		
	


OBJ = $(SRC:.c=.o)

Head = ./mandatory/includes/cub3d.h

libft_DIR = ./mandatory/42_Libft
libft = $(libft_DIR)/libft.a


NAME = cub3D

all: clean $(NAME)

$(NAME): $(OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBRARIES) $(libft) -o $(NAME) -lm && make clean


%.o: %.c $(INC) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	@make -C $(libft_DIR) clean
	@rm -f $(OBJ)

fclean: clean
#	@make -C $(libft_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re