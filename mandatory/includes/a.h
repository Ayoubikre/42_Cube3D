/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:00:00 by noctis            #+#    #+#             */
/*   Updated: 2025/12/03 05:31:32 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# ifdef __linux__
#  include "../../Tools/mlx/linux/MLX42.h"
# else
#  include "../../Tools/mlx/macOS/MLX42.h"
# endif

# include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                                Engine Constants                            */
/* -------------------------------------------------------------------------- */

# define WIDTH 1100
# define HEIGHT 1080
# define TEX_COUNT 6
# define ELEM_COUNT 8

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR 4
# define PORTAL 5

/* -------------------------------------------------------------------------- */
/*                                 Sub-Structs                                */
/* -------------------------------------------------------------------------- */

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		grid_x;
	int		grid_y;
	int		cell_s;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	orientation;
	double	mouse_l_p;
}	t_player;

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

typedef struct s_mini
{
	mlx_image_t		*ptr_img;
	int32_t			id_img;
	double			mini_w;
	double			mini_h;
	int				m_player_size;
	int				m_cell_size;
}	t_mini;

/* -------------------------------------------------------------------------- */
/*                                   t_data                                   */
/*                          (one complete level content)                      */
/* -------------------------------------------------------------------------- */

typedef struct s_data
{
	int			parsed[ELEM_COUNT];
	char		*textures[TEX_COUNT];
	t_texture	load_textures[TEX_COUNT];
	t_color		floor_color;
	t_color		ceiling_color;
    
	t_map		map;
	t_player	player;
	t_mini		mini;
	struct s_ray *rays;

	double		fov;
	double		ang;
	double		move_speed;
}	t_data;

/* -------------------------------------------------------------------------- */
/*                                 t_level Node                                */
/*                 (linked list node that stores one whole map)              */
/* -------------------------------------------------------------------------- */

typedef struct s_level
{
	char			*path;      /* Path to map.cub */
	t_data			*data;      /* Fully parsed level data */
	struct s_level	*next;
	struct s_level	*prev;
}	t_level;

/* -------------------------------------------------------------------------- */
/*                                     t_game                                 */
/*              (the global engine: one MLX, one window, many levels)        */
/* -------------------------------------------------------------------------- */

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*main_img;

	t_level		*levels;      /* head of level list */
	t_level		*current;     /* current active level */
}	t_game;

#endif
