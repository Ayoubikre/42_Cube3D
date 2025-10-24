/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:45:27 by noctis            #+#    #+#             */
/*   Updated: 2025/10/24 11:19:44 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define WIDTH 512
# define HEIGHT 512

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

#endif