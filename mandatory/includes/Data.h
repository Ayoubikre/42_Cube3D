/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:45:27 by noctis            #+#    #+#             */
/*   Updated: 2025/10/27 17:11:46 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# ifdef __linux__
#  include "../../Tools/mlx/linux/MLX42.h"
# else
#  include "../../Tools/mlx/macOS/MLX42.h"
# endif

# define WIDTH 1280
# define HEIGHT 565

// # define WIDTH 800
// # define HEIGHT 600

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

# define M_PI 	3.14159265358979323846
# define RAD(x)  (x * M_PI / 180.0)
# define FOV 	data->player.fov
# define ANG 	data->player.start_angle


typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	char		orientation;
	int 		size;
	double 		start_angle;
	double 		fov;
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
	int			cell_size;
}				t_map;

typedef struct s_mlx
{
	mlx_t* ptr;
	mlx_image_t* ptr_img;
	int32_t id_img;
}			t_mlx;

typedef struct s_data
{
	int			parsed[ELEM_COUNT];
	char		*textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_mlx		mlx;
	t_player	player;
}				t_data;

#endif
