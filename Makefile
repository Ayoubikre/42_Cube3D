
#----------------------------------   Platform detection :

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    MLX_LIBRARIES = Tools/mlx/linux/libmlx42_combined.a \
        -lX11 -lXrandr -lXinerama -lXcursor -lXi -lGL -lm -ldl -lpthread
else
    MLX_LIBRARIES = Tools/mlx/macOS/libmlx42_combined.a \
        -framework Cocoa -framework OpenGL -framework IOKit -lm -ldl
endif

#---------------------------------------------------------------#

CC = cc

CFLAGS  = -Wall
# CFLAGS  = -Wall -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra -fsanitize=address -g
# CFLAGS  = -Wall -Werror -Wextra


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

Rays = 	mandatory/Raycasting/a.c \

SRC = $(Parse) \
		$(Rays) \


OBJ = $(SRC:.c=.o)

Head = ./mandatory/includes/cub3d.h

libft_DIR = ./mandatory/42_Libft
libft = $(libft_DIR)/libft.a


NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
#	@make -C $(libft_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIBRARIES) $(libft) -o $(NAME)  

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