/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:34:32 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/22 23:02:04 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../42_Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include "../../Tools/mlx/linux/MLX42.h"
# else
#  include "../../Tools/mlx/macOS/MLX42.h"
# endif

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define TEX_COUNT 4
# define ELEM_NO 0
# define ELEM_SO 1
# define ELEM_WE 2
# define ELEM_EA 3
# define ELEM_F 4
# define ELEM_C 5
# define ELEM_COUNT 6

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	char		orientation;
}				t_player;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_data
{
	char		*textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_player	player;
	int			parsed[ELEM_COUNT];
}				t_data;

int				main(int ac, char **av);

// -------------------------------------------- Parsing:

int				parse_file(char *filename, t_data *data);
int				main_core(t_data *data, char *file_name);

int				check_file(char *filename, int flag);

int				parse_texture_line(char *line, t_data *data);
int				parse_color_line(char *line, t_data *data);
int				parse_rgb(char *str, t_color *color);

int				is_texture_line(char *line);
int				is_element_line(char *line);
int				is_map_line(char *line);

int				parse_map(int fd, t_data *data, char *first_line);
int				store_map_line(t_data *data, char *line);

int				validate_map(t_data *data);
int				check_map_closed(t_data *data);
int				check_map_characters(t_data *data);
int				find_player(t_data *data);
int				validate_elements_complete(t_data *data);
int				all_elements_parsed(t_data *data);

int				is_empty_line(char *line);
char			*skip_spaces(char *str);
int				is_map_char(char c);
int				ft_isspace(char c);
void			set_player_data(t_data *data, int i, int j);
char			get_char_at(t_data *data, int y, int x);
int				is_valid_pos(char c);
int				is_player_char(char c);

void			print_error(char *msg);
void			free_data(t_data *data);
void			free_map(t_map *map);

void			init_data(t_data *data);

// -------------------------------------------- Raycasting:

#endif