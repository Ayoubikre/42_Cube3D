/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/10/29 16:42:46 by noctis           ###   ########.fr       */
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

// void	ft_update_mouse_angle(t_data *data)
// {
// 	static double last_x = -1.0;
// 	int x, y;

// 	mlx_get_mouse_pos(data->mlx.ptr, &x, &y);

// 	if (last_x < 0)
// 	{
// 		last_x = (double)x;
// 		return;
// 	}

// 	double dx = (double)x - last_x;
// 	last_x = (double)x;

// 	double sensitivity = 0.0005; // tweak to taste
// 	data->player.start_angle += dx * sensitivity;

// 	// Normalize angle between 0 and 2π
// 	if (data->player.start_angle < 0)
// 		data->player.start_angle += 2 * M_PI;
// 	if (data->player.start_angle >= 2 * M_PI)
// 		data->player.start_angle -= 2 * M_PI;

// 	// Optionally recenter the cursor to the middle each frame
// 	mlx_set_mouse_pos(data->mlx.ptr, WIDTH / 2, HEIGHT / 2);
// 	last_x = WIDTH / 2; // reset last_x to the middle
// }



int	ft_find_walls(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.grid_x)
		return (1);
	if (y < 0 || y >= data->map.grid_y)
		return (1);
	if (data->map.grid[y][x] == '1')
		return (1);
	return (0);
}

int	ft_buffer(t_data *data, double x, double y)
{
	double	buffer;

	buffer = 0.1;
	if (ft_find_walls(data, (int)floor(x), (int)floor(y)))
		return (1);
	if (ft_find_walls(data, (int)floor(x + buffer), (int)floor(y + buffer)))
		return (1);
	if (ft_find_walls(data, (int)floor(x - buffer), (int)floor(y - buffer)))
		return (1);
	if (ft_find_walls(data, (int)floor(x + buffer), (int)floor(y - buffer)))
		return (1);
	if (ft_find_walls(data, (int)floor(x - buffer), (int)floor(y + buffer)))
		return (1);
	return (0);
}

double	ft_if_valid_moves(t_data *data, double r, int f, int i)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_ang;

	tmp_x = data->player.pos_x;
	tmp_y = data->player.pos_y;
	while (++i < 5)
	{
		tmp_ang = ANG + ((f == 1) * M_PI) + ((f == 2) * M_PI / 2) - ((f == 3)
				* M_PI / 2);
		if (!ft_buffer(data, tmp_x + cos(tmp_ang) * r, tmp_y + sin(tmp_ang) * r))
			return (r);
		r /= 2.0;
	}
	return (-1);
}

void	ft_capture_player_moves(t_data *data)
{
	double	r;
	
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_W))
	{
		if ((r=ft_if_valid_moves(data, 0.1, 0, -1)) !=-1)
		{
			data->player.pos_x += cos(ANG) * r;
			data->player.pos_y += sin(ANG) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
	{
		if ((r=ft_if_valid_moves(data, 0.1, 1, -1)) !=-1)
		{
			data->player.pos_x -= cos(ANG) * r;
			data->player.pos_y -= sin(ANG) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
	{
		if ((r=ft_if_valid_moves(data, 0.1, 2, -1)) !=-1)
		{
			data->player.pos_x += cos(ANG + M_PI / 2) * r;
			data->player.pos_y += sin(ANG + M_PI / 2) * r;
		}
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
	{
		if ((r=ft_if_valid_moves(data, 0.1, 3, -1)) !=-1)
		{
			data->player.pos_x += cos(ANG - M_PI / 2) * r;
			data->player.pos_y += sin(ANG - M_PI / 2) * r;
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
	
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
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
	
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			i = -1;
			while (++i < data->map.cell_size)
			{
				j = -1;
				while (++j < data->map.cell_size)
				{
					px = x * data->map.cell_size + i;
					py = y * data->map.cell_size + j;
					if (py < HEIGHT / 2)
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xFFFFFFA1);
				}
			}
		}
	}
}


// void ft_draw_minimap(t_data *data)
// {
//     const int   mini_w   = data->mini.mini_w;
//     const int   mini_h   = data->mini.mini_h;
//     const int   map_w    = data->map.grid_x;
//     const int   map_h    = data->map.grid_y;

//     // Scale to fit entire map in minimap (keep square cells)
//     const float scale_x  = (float)mini_w / map_w;
//     const float scale_y  = (float)mini_h / map_h;
//     const float scale    = fminf(scale_x, scale_y);
//     const int   cell     = (int)scale;

//     const int   center_x = mini_w / 2;
//     const int   center_y = mini_h / 2;

//     int   draw_x, draw_y;
//     int   i, j;

//     /* ------------------------------------------------------------- */
//     /* 1. Clear minimap                                              */
//     /* ------------------------------------------------------------- */
//     for (int y = 0; y < mini_h; ++y)
//         for (int x = 0; x < mini_w; ++x)
//             mlx_put_pixel(data->mini.ptr_img, x, y, 0x000000FF);

//     /* ------------------------------------------------------------- */
//     /* 2. Compute visible map area (player at centre)                */
//     /* ------------------------------------------------------------- */
//     float player_map_x = data->player.pos_x;
//     float player_map_y = data->player.pos_y;

//     float visible_cells_x = mini_w / (2.0f * scale);
//     float visible_cells_y = mini_h / (2.0f * scale);

//     int start_x = (int)(player_map_x - visible_cells_x);
//     int start_y = (int)(player_map_y - visible_cells_y);
//     int end_x   = (int)(player_map_x + visible_cells_x) + 1;
//     int end_y   = (int)(player_map_y + visible_cells_y) + 1;

//     /* ------------------------------------------------------------- */
//     /* 3. Draw solid map cells (your colors, no lines)               */
//     /* ------------------------------------------------------------- */
//     for (int gy = start_y; gy < end_y; ++gy)
//     {
//         for (int gx = start_x; gx < end_x; ++gx)
//         {
//             if (gx < 0 || gx >= map_w || gy < 0 || gy >= map_h)
//                 continue;

//             // Cell centre in map space → minimap pixel
//             float cell_center_x = gx * scale + scale * 0.5f;
//             float cell_center_y = gy * scale + scale * 0.5f;

//             draw_x = (int)(center_x + (cell_center_x - player_map_x * scale));
//             draw_y = (int)(center_y + (cell_center_y - player_map_y * scale));

//             uint32_t color = (data->map.grid[gy][gx] == '1')
//                              ? 0x350707A1   // wall
//                              : 0xF5DEB388;  // floor

//             int half = cell / 2;
//             for (i = -half; i < half; ++i)
//                 for (j = -half; j < half; ++j)
//                 {
//                     int px = draw_x + i;
//                     int py = draw_y + j;
//                     if (px >= 0 && px < mini_w && py >= 0 && py < mini_h)
//                         mlx_put_pixel(data->mini.ptr_img, px, py, color);
//                 }
//         }
//     }

//     /* ------------------------------------------------------------- */
//     /* 4. Draw player (red square + white dot)                       */
//     /* ------------------------------------------------------------- */
//     int p_size = (int)fmaxf(cell * 0.4f, 3);

//     for (i = -p_size; i <= p_size; ++i)
//         for (j = -p_size; j <= p_size; ++j)
//         {
//             int px = center_x + i;
//             int py = center_y + j;
//             if (px >= 0 && px < mini_w && py >= 0 && py < mini_h)
//                 mlx_put_pixel(data->mini.ptr_img, px, py, 0xFF0000FF);
//         }
//     mlx_put_pixel(data->mini.ptr_img, center_x, center_y, 0xFFFFFFFF);

//     /* ------------------------------------------------------------- */
//     /* 5. Draw direction ray (yellow)                                */
//     /* ------------------------------------------------------------- */
//     int ray_len = (int)(cell * 2.5f);
//     int rx = center_x + (int)(cos(ANG) * ray_len);
//     int ry = center_y + (int)(sin(ANG) * ray_len);

//     int dx = abs(rx - center_x), sx = center_x < rx ? 1 : -1;
//     int dy = -abs(ry - center_y), sy = center_y < ry ? 1 : -1;
//     int err = dx + dy, e2;
//     int x0 = center_x, y0 = center_y;

//     while (1)
//     {
//         if (x0 >= 0 && x0 < mini_w && y0 >= 0 && y0 < mini_h)
//             mlx_put_pixel(data->mini.ptr_img, x0, y0, 0xFFFF00FF);
//         if (x0 == rx && y0 == ry) break;
//         e2 = 2 * err;
//         if (e2 >= dy) { err += dy; x0 += sx; }
//         if (e2 <= dx) { err += dx; y0 += sy; }
//     }
// }


void	draw_single_ray(t_data *data, double ray_angle)
{
    // Starting point: player position in pixels
    int x0 = (int)(data->player.pos_x * data->map.cell_size);
    int y0 = (int)(data->player.pos_y * data->map.cell_size);

    int x1 = (int)(x0 + cos(ray_angle) * 50);
    int y1 = (int)(y0 + sin(ray_angle) * 50);

    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        mlx_put_pixel(data->mlx.ptr_img, x0, y0, 0xFF0000); 

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
	ft_draw_background(data, 0 ,0);
	ft_draw_map_2d(data, 0, 0);
	ft_capture_player_moves(data);
	// ft_update_mouse_angle(data);
	ft_draw_player_2d(data, 0, 0);
	draw_single_ray(data, data->player.start_angle);

	
	// ft_draw_minimap(data);
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

		
	data->map.cell_size = (int)fmin(HEIGHT / data->map.grid_y, WIDTH
			/ data->map.grid_x);
	data->player.size = (int)fmax(data->map.cell_size / 8, 4);


	data->mini.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH / 5, HEIGHT / 3);
	if (!data->mini.ptr_img)
		return (mlx_terminate(data->mlx.ptr), -1);
		
	data->mini.id_img = mlx_image_to_window(data->mlx.ptr, data->mini.ptr_img, 10,
			10);
	if (data->mini.id_img == -1)
		return (mlx_terminate(data->mlx.ptr), -1);
		
	data->mini.mini_w=WIDTH / 6;
	data->mini.mini_h=HEIGHT / 4;
	data->mini.m_cell_size=(int)fmin(data->mini.mini_h / data->map.grid_y,data->mini.mini_w / data->map.grid_x);
	data->player.m_size = (int)fmax(data->mini.m_cell_size / 8, 4);
	
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
