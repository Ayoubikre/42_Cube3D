
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
CFLAGS  = -Wall -Werror -Wextra


Parse = mandatory/main.c \
		mandatory/parsing/utils.c \
		mandatory/parsing/parsing.c \
		mandatory/parsing/parsing_utils.c \
	  	mandatory/parsing/textures.c \
		mandatory/parsing/color.c \
		mandatory/parsing/color_utils.c \
		mandatory/parsing/init.c \
		mandatory/parsing/map.c \
		mandatory/parsing/map_utils.c \
		mandatory/parsing/map_utils2.c

Rays = 	mandatory/Raycasting/ft_raycast.c \

SRC = $(Parse) \
		$(Rays) \


OBJ = $(SRC:.c=.o)

Head = ./mandatory/includes/cub3d.h

libft_DIR = ./mandatory/42_Libft
libft = $(libft_DIR)/libft.a


NAME = cub3D

all: clean $(NAME)

$(NAME): $(OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBRARIES) $(libft) -o $(NAME) -lm && $(add)

%.o: %.c $(INC) $(libft_DIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
#	@make -C $(libft_DIR) clean
	rm -f $(OBJ)

fclean: clean
#	@make -C $(libft_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re