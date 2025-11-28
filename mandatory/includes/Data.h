/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:45:27 by noctis            #+#    #+#             */
/*   Updated: 2025/11/27 21:48:47 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# ifdef __linux__
#  include "../../Tools/mlx/linux/MLX42.h"
# else
#  include "../../Tools/mlx/macOS/MLX42.h"
# endif

# define WIDTH 1100
# define HEIGHT 1080

// # define WIDTH 800
// # define HEIGHT 600

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR 4
# define PORTAL 5

# define TEX_COUNT 6
# define ELEM_NO 0
# define ELEM_SO 1
# define ELEM_WE 2
# define ELEM_EA 3
# define ELEM_DR 4
# define ELEM_PR 5
# define ELEM_F 6
# define ELEM_C 7
# define ELEM_COUNT 8

# define M_PI 3.14159265358979323846
# define VISIBLE_DISTANCE 100
# define RAYS WIDTH
# define MOUSE_SP 0.002

typedef struct	s_render_vars
{
	double		proj;
	int			column;
	int			ray_i;
	double		wall_dist;
	int			lineH;
	int			drawStart;
	int			drawEnd;
	int			ray_side;
}				t_render_vars;

typedef struct s_ray
{
	int			i;
	double		angle;
	double		ang_cos;
	double		ang_sin;
	int			x;
	int			y;
	double		const_x;
	double		const_y;
	double		extra_x;
	double		extra_y;
	double		len;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	char		drc;
}				t_ray;

typedef struct s_minimap
{
	mlx_image_t	*ptr_img;
	int32_t		id_img;
	double		mini_w;
	double		mini_h;
	int			m_player_size;
	int			m_cell_size;
}				t_mini;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	char		orientation;
	double		mouse_l_p;
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
	int			grid_x;
	int			grid_y;
	int			cell_s;
}				t_map;

typedef struct s_mlx
{
	mlx_t		*ptr;
	mlx_image_t	*ptr_img;
	int32_t		id_img;
}				t_mlx;

typedef struct s_texture
{
	mlx_texture_t	*tex;
	unsigned int	width;
	unsigned int	height;
	uint8_t			*pixels;
	int				bytes_per_pixel;
	int				loaded;
	xpm_t			*xpm;
}	t_texture;

typedef struct s_data
{
	int			parsed[ELEM_COUNT];
	char		*textures[TEX_COUNT];
	t_texture	load_textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
	t_mlx		mlx;
	t_player	player;
	t_mini		mini;
	t_ray		*rays;
	double		fov;
	double		ang;
	double		move_speed;
}				t_data;

#endif
