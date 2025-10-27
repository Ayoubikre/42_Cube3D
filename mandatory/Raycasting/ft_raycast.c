/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/10/27 18:05:49 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx.ptr);
}


// int	ft_find_walls(t_data *data, int x, int y)
// {
// 	if (x < 0 || x >= data->map.width)
// 		return (1);
// 	if (y < 0 || y >= data->map.height)
// 		return (1);
// 	if (data->map.grid[y][x] == '1')
// 		return (1);
// 	return (0);
// }

// int	ft_check_collision(t_data *data, double new_x, double new_y)
// {
// 	double	radius;
	
// 	// Collision radius in map units (adjust based on your needs)
// 	radius = 0.05; // padding from the wall
	
// 	// Check center
// 	if (ft_find_walls(data, (int)floor(new_x), (int)floor(new_y)))
// 		return (1);
	
// 	// Check 4 cardinal directions
// 	if (ft_find_walls(data, (int)floor(new_x + radius), (int)floor(new_y)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x - radius), (int)floor(new_y)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x), (int)floor(new_y + radius)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x), (int)floor(new_y - radius)))
// 		return (1);
	
// 	// Check 4 diagonal corners
// 	if (ft_find_walls(data, (int)floor(new_x + radius), (int)floor(new_y + radius)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x + radius), (int)floor(new_y - radius)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x - radius), (int)floor(new_y + radius)))
// 		return (1);
// 	if (ft_find_walls(data, (int)floor(new_x - radius), (int)floor(new_y - radius)))
// 		return (1);
	
// 	return (0);
// }

// void	ft_capture_player_moves(t_data *data)
// {
// 	double	move_x;
// 	double	move_y;
// 	double	speed;

// 	speed = 0.1;
// 	move_x = 0;
// 	move_y = 0;
	
// 	// Calculate movement vector based on input
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_W))
// 	{
// 		move_x += cos(ANG) * speed;
// 		move_y += sin(ANG) * speed;
// 	}
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
// 	{
// 		move_x -= cos(ANG) * speed;
// 		move_y -= sin(ANG) * speed;
// 	}
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
// 	{
// 		move_x += cos(ANG + M_PI / 2) * speed;
// 		move_y += sin(ANG + M_PI / 2) * speed;
// 	}
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
// 	{
// 		move_x += cos(ANG - M_PI / 2) * speed;
// 		move_y += sin(ANG - M_PI / 2) * speed;
// 	}
	
// 	// Apply X movement if valid (allows sliding along Y-axis walls)
// 	if (move_x != 0 && !ft_check_collision(data, 
// 		data->player.pos_x + move_x, data->player.pos_y))
// 		data->player.pos_x += move_x;
	
// 	// Apply Y movement if valid (allows sliding along X-axis walls)
// 	if (move_y != 0 && !ft_check_collision(data, 
// 		data->player.pos_x, data->player.pos_y + move_y))
// 		data->player.pos_y += move_y;
	
// 	// Handle rotation
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_LEFT))
// 		data->player.start_angle -= RAD(2);
// 	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_RIGHT))
// 		data->player.start_angle += RAD(2);
// }


int	ft_find_walls(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.width)
		return (1);
	if (y < 0 || y >= data->map.height)
		return (1);
	if (data->map.grid[y][x] == '1')
		return (1);
	return (0);
}


int	ft_if_valid_moves(t_data *data, double *r, int f)
{
	int		i;
	double	tmp_x;
	double	tmp_y;

	i = -1;
	tmp_x = data->player.pos_x;
	tmp_y = data->player.pos_y;
	while (++i < 5)
	{
		if (f == 0 && !ft_find_walls(data,
			floor(tmp_x + cos(ANG) * (*r)), floor(tmp_y + sin(ANG) * (*r))))
			return (1);
		if (f == 1 && !ft_find_walls(data, floor(tmp_x - cos(ANG) * (*r)), floor(tmp_y - sin(ANG) * (*r))))
			return (1);
		if (f == 2 && !ft_find_walls(data, floor(tmp_x + cos(ANG + M_PI /2) * (*r)),floor(tmp_y + sin(ANG + M_PI /2) * (*r))))
			return (1);
		if (f == 3 && !ft_find_walls(data, floor(tmp_x + cos(ANG - M_PI /2) * (*r)),floor(tmp_y + sin(ANG - M_PI /2) * (*r))))
			return (1);
		(*r) /= 2.0;
	}
	return (0);
}


void	ft_capture_player_moves(t_data *data)
{
	double	r;

	r = 0.1;
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_W))
	{
		if (ft_if_valid_moves(data, &r, 0))
		{
			data->player.pos_x += cos(ANG) * r;
			data->player.pos_y += sin(ANG) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
	{
		if (ft_if_valid_moves(data, &r, 1))
		{
			data->player.pos_x -= cos(ANG) * r;
			data->player.pos_y -= sin(ANG) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
	{
		if (ft_if_valid_moves(data, &r, 2))
		{
			data->player.pos_x += cos(ANG + M_PI/2) * r;
			data->player.pos_y += sin(ANG + M_PI/2) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
	{
		if (ft_if_valid_moves(data, &r, 3))
		{
			data->player.pos_x += cos(ANG - M_PI/2) * r;
			data->player.pos_y += sin(ANG - M_PI/2) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_LEFT))
	{
		data->player.start_angle -= RAD(2);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_RIGHT))
	{
		data->player.start_angle += RAD(2);
	}
}

void	ft_draw_player_2d(t_data *data, uint32_t px, uint32_t py)
{
	int (s), (player_px), (player_py), (j), i = -1;
	
	s = data->player.size;
	player_px = data->player.pos_x * data->map.cell_size;
	player_py = data->player.pos_y * data->map.cell_size;
	while (++i <= s * 2) // draw the black square
	{
		j = -1;
		while (++j <= s * 2)
		{
			px = (player_px - s) + i;
			py = (player_py - s) + j;
			mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
		}
	}
	mlx_put_pixel(data->mlx.ptr_img, player_px, player_py, 0xFFFFFF); // draw the center point
}

void	ft_draw_map_2d(t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	
	while (++x < data->map.width)
	{
		y = -1;
		while (++y < data->map.height)
		{
			i = -1;
			while (++i < data->map.cell_size)
			{
				j = -1;
				while (++j < data->map.cell_size)
				{
					px = x * data->map.cell_size + i;
					py = y * data->map.cell_size + j;
					if (data->map.grid[y][x] == '1')
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x350707A1);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xF5DEB388);
				}
			}
		}
	}
}

void	ft_draw_background(t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	
	while (++x < data->map.width)
	{
		y = -1;
		while (++y < data->map.height)
		{
			i = -1;
			while (++i < data->map.cell_size)
			{
				j = -1;
				while (++j < data->map.cell_size)
				{
					px = x * data->map.cell_size + i;
					py = y * data->map.cell_size + j;
					if (y < data->map.height / 2)
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xFFFFFFA1);
				}
			}
		}
	}
}

void	draw_single_ray(t_data *data, double ray_angle)
{
    // Starting point: player position in pixels
    int x0 = (int)(data->player.pos_x * data->map.cell_size);
    int y0 = (int)(data->player.pos_y * data->map.cell_size);

    // Calculate end point using angle and length
    int x1 = (int)(x0 + cos(data->player.start_angle) * 50);
    int y1 = (int)(y0 + sin(data->player.start_angle) * 50);

    // Bresenham-like line drawing
    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        // Draw pixel
        mlx_put_pixel(data->mlx.ptr_img, x0, y0, 0xFF0000); // red line

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void	ft_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// ft_draw_background(data, 0 ,0);
	ft_draw_map_2d(data, 0, 0);
	ft_capture_player_moves(data);
	ft_draw_player_2d(data, 0, 0);
	draw_single_ray(data, data->player.start_angle);
}

int	ft_init_game(t_data *data)
{
	data->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!data->mlx.ptr)
		return (-1);
	data->mlx.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	if (!data->mlx.ptr_img)
		return (mlx_terminate(data->mlx.ptr), -1);
	data->mlx.id_img = mlx_image_to_window(data->mlx.ptr, data->mlx.ptr_img, 0,
			0);
	if (data->mlx.id_img == -1)
		return (mlx_terminate(data->mlx.ptr), -1);
	data->map.cell_size = (int)fmin(HEIGHT / data->map.height, WIDTH
			/ data->map.width);
	data->player.size = (int)fmax(data->map.cell_size / 8, 4);

	return (0);
}

int	ft_start(t_data *data)
{
	if (ft_init_game(data) == -1)
		return (-1);
	mlx_key_hook(data->mlx.ptr, ft_capture_keys, (void *)data);
	mlx_loop_hook(data->mlx.ptr, ft_all, (void *)data);
	mlx_loop(data->mlx.ptr);
	mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
	mlx_terminate(data->mlx.ptr);
	return (0);
}
