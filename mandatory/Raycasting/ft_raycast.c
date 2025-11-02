/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/11/02 21:49:08 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


//----------------------------------------------
//------------------------------ keys :
//----------------------------------------------

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	(void) keydata;
	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx.ptr);
}



//----------------------------------------------
//------------------------------ player moves :
//----------------------------------------------

void	ft_update_mouse_angle(double xpos, double ypos, void *param)
{
	t_data	*data;
	double	new_x;

	(void)ypos;
	data = (t_data *)param;
	if (data->player.mouse_l_p == -1)
	{
		data->player.mouse_l_p = xpos;
		return ;
	}
	new_x = xpos - data->player.mouse_l_p;
	data->player.mouse_l_p = xpos;
	ANG += new_x * mouse_speed;
	if (ANG < 0)
		ANG += 2 * M_PI;
	else if (ANG >= 2 * M_PI)
		ANG -= 2 * M_PI;
}

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

int	ft_padding(t_data *data, double x, double y)
{
	double	padding;

	padding = 0.1;
	if (ft_find_walls(data, (int)floor(x), (int)floor(y)))
		return (1);
	if (ft_find_walls(data, (int)floor(x + padding), (int)floor(y + padding)))
		return (1);
	if (ft_find_walls(data, (int)floor(x - padding), (int)floor(y - padding)))
		return (1);
	if (ft_find_walls(data, (int)floor(x + padding), (int)floor(y - padding)))
		return (1);
	if (ft_find_walls(data, (int)floor(x - padding), (int)floor(y + padding)))
		return (1);
	return (0);
}

int	ft_move(t_data *data, double move_x, double move_y, double r)
{
	int		i;
	double	new_x;
	double	new_y;

	i = -1;
	while (++i < 5)
	{
		new_x = data->player.pos_x + (move_x * r);
		new_y = data->player.pos_y + (move_y * r);
		if (!ft_padding(data, new_x, new_y))
		{
			return (data->player.pos_x = new_x, data->player.pos_y = new_y, 1);
		}
		if (!ft_padding(data, new_x, data->player.pos_y))
		{
			return (data->player.pos_x = new_x, 1);
		}
		if (!ft_padding(data, data->player.pos_x, new_y))
		{
			return (data->player.pos_y = new_y, 1);
		}
		r /= 2.0;
	}
	return (0);
}

void	ft_capture_player_moves(t_data *data)
{
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_W))
	{
		ft_move(data, cos(ANG), sin(ANG), 0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
	{
		ft_move(data, -cos(ANG), -sin(ANG), 0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
	{
		ft_move(data, cos(ANG + M_PI / 2), sin(ANG + M_PI / 2), 0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
	{
		ft_move(data, cos(ANG - M_PI / 2), sin(ANG - M_PI / 2), 0.1);
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



//----------------------------------------------
//------------------------------ player draw 2D:
//----------------------------------------------

void	ft_draw_player_2d(t_data *data, uint32_t px, uint32_t py)
{
	int (s), (player_px), (player_py), (j), i = -1;
	s = (int)fmax(CELL_S / 8, 4);
	player_px = data->player.pos_x * CELL_S;
	player_py = data->player.pos_y * CELL_S;
	while (++i <= s * 2)
	{
		j = -1;
		while (++j <= s * 2)
		{
			px = (player_px - s) + i;
			py = (player_py - s) + j;
			mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
		}
	}
	mlx_put_pixel(data->mlx.ptr_img, player_px, player_py, 0xFFFFFF);
}



//----------------------------------------------
//------------------------------ map draw 2D :
//----------------------------------------------

void	ft_draw_map_2d(t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			i = -1;
			while (++i < CELL_S)
			{
				j = -1;
				while (++j < CELL_S)
				{
					px = x * CELL_S + i;
					py = y * CELL_S + j;
					if (data->map.grid[y][x] == '1')
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x350707A1);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xF5DEB388);
				}
			}
		}
	}
}



//----------------------------------------------
//------------------------------ Bg draw :
//----------------------------------------------

void	ft_draw_background(t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			i = -1;
			while (++i < CELL_S)
			{
				j = -1;
				while (++j < CELL_S)
				{
					px = x * CELL_S + i;
					py = y * CELL_S + j;
					if (y < data->map.grid_y / 2)
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xFFFFFFA1);
				}
			}
		}
	}
}



//----------------------------------------------
//------------------------------ Draw Rays :
//----------------------------------------------

void	ft_draw_ray(t_data *data, double angle, int f, double ray_len)
{
    int x0 = (int)((data->player.pos_x * CELL_S)) ;
    int y0 = (int)((data->player.pos_y * CELL_S));
    double len_in_pixels = (ray_len ) * CELL_S;
	int x1,y1;
	if(f){
		x1 = (int)(x0 + cos(angle) * len_in_pixels);
		y1 = (int)(y0 + sin(angle) * len_in_pixels);
	}
	else{
		x1 = (int)(x0 + cos(angle) * ray_len);
		y1 = (int)(y0 + sin(angle) * ray_len);
	}
    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;
    while (1)
    {
		if(f)
			mlx_put_pixel(data->mlx.ptr_img, x0, y0, 0xADD8E6FF);
		else
			mlx_put_pixel(data->mlx.ptr_img, x0, y0, 0xFF0000FF); 
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy){
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            err += dx;
            y0 += sy;
        }
    }
}



//----------------------------------------------
//------------------------------ Raycasting :
//----------------------------------------------


void	ft_raycasting(t_data *data)
{
	int i;
	double r;

	FOV = RAD(90);
	r = FOV / RAYS;
	i = -1;

	while (++i < RAYS)
	{
		RAY(i).angle = (ANG - (FOV / 2)) + (i * r);
		if (RAY(i).angle < 0)
			RAY(i).angle += 2 * M_PI;
		else if (RAY(i).angle >= 2 * M_PI)
			RAY(i).angle -= 2 * M_PI;

		RAY(i).ang_cos = cos(RAY(i).angle);
		RAY(i).ang_sin = sin(RAY(i).angle);
		RAY(i).const_x = fabs(CELL_S / RAY(i).ang_cos);
		RAY(i).const_y = fabs(CELL_S / RAY(i).ang_sin);
		RAY(i).x = floor(data->player.pos_x);
		RAY(i).y = floor(data->player.pos_y);

		if (RAY(i).ang_cos < 0)
		{
			RAY(i).step_x = -1;
			RAY(i).extra_x = (data->player.pos_x - RAY(i).x) * RAY(i).const_x;
		}
		else
		{
			RAY(i).step_x = 1;
			RAY(i).extra_x = (RAY(i).x + 1.0 - data->player.pos_x) * RAY(i).const_x;
		}

		if (RAY(i).ang_sin < 0)
		{
			RAY(i).step_y = -1;
			RAY(i).extra_y = (data->player.pos_y - RAY(i).y) * RAY(i).const_y;
		}
		else
		{
			RAY(i).step_y = 1;
			RAY(i).extra_y = (RAY(i).y + 1.0 - data->player.pos_y) * RAY(i).const_y;
		}

		RAY(i).hit = 0;
		while (RAY(i).hit == 0)
		{
			if (RAY(i).extra_x < RAY(i).extra_y)
			{
				RAY(i).extra_x += RAY(i).const_x;
				RAY(i).x += RAY(i).step_x;
				RAY(i).len = (RAY(i).x - data->player.pos_x + (1 - RAY(i).step_x) / 2) / RAY(i).ang_cos;
				RAY(i).side = 0;
			}
			else
			{
				RAY(i).extra_y += RAY(i).const_y;
				RAY(i).y += RAY(i).step_y;
				RAY(i).len = (RAY(i).y - data->player.pos_y + (1 - RAY(i).step_y) / 2) / RAY(i).ang_sin;
				RAY(i).side = 1;
			}
			if (data->map.grid[RAY(i).y][RAY(i).x] == '1')
				RAY(i).hit = 1;
		}
			ft_draw_ray(data, RAY(i).angle , 1, RAY(i).len);
	}	
	ft_draw_ray(data, ANG,0,50);
	ft_draw_ray(data, ANG - ( FOV / 2),0,50);
	ft_draw_ray(data, ANG + ( FOV / 2),0,50);
}


//----------------------------------------------
//------------------------------ clean :
//----------------------------------------------

void ft_clean(t_data *data, int f)
{	
	if(f>=0)
		mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
	if(f>=1)
		mlx_delete_image(data->mlx.ptr, data->mini.ptr_img);
	if(f>=2)
		free(data->rays);
	// if(f>=3)
	// {	
	// }
	mlx_terminate(data->mlx.ptr);
}
	


//----------------------------------------------
//------------------------------ the Engine :
//----------------------------------------------

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// ft_draw_background(data, 0, 0);
	ft_draw_map_2d(data, 0, 0);
	ft_capture_player_moves(data);
	ft_draw_player_2d(data, 0, 0);
	ft_raycasting(data);


	
	// struct timeval tv;
	// gettimeofday(&tv, NULL);
	// data->final_time = tv.tv_sec;
	// if(data->final_time - data->init_time >= 1)
	// {
	// 	printf("fps : %d\n", data->fps);
	// 	data->init_time = data->final_time;
	// 	data->fps = 0;
	// }
	// else
	// 	(data->fps)++;
	
}



//----------------------------------------------
//------------------------------ hooks :
//----------------------------------------------

void ft_hooks(t_data *data)
{
	mlx_key_hook(data->mlx.ptr, ft_capture_keys, (void *)data);
	mlx_cursor_hook(data->mlx.ptr, ft_update_mouse_angle, (void *)data);
	mlx_set_cursor_mode(data->mlx.ptr, MLX_MOUSE_DISABLED);
}



//----------------------------------------------
//------------------------------ init :
//----------------------------------------------

int ft_init_mlx_map(t_data *data)
{
	data->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", false);
	if (!data->mlx.ptr)
		return (-1);
	data->mlx.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	if (!data->mlx.ptr_img)
		return (-1);
	data->mlx.id_img = mlx_image_to_window(data->mlx.ptr, data->mlx.ptr_img, 0, 0);
	if (data->mlx.id_img == -1)
		return (-1);
	CELL_S = (int)fmin(HEIGHT / data->map.grid_y, WIDTH / data->map.grid_x);
	return (0);
}

int ft_init_mlx_minimap(t_data *data)
{
	data->mini.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH / 5, HEIGHT / 3);
	if (!data->mini.ptr_img)
		return (-1);
	data->mini.id_img = mlx_image_to_window(data->mlx.ptr, data->mini.ptr_img, 10,
			10);
	if (data->mini.id_img == -1)
		return (-1);
	return 0;
}

int ft_init_rays(t_data *data)
{
	data->rays=malloc(sizeof(t_ray) * RAYS);
	if(!data->rays)
		return -1;
	ft_memset(data->rays, 0, sizeof(t_ray) * RAYS);
	return 0;
}

int	ft_init_game(t_data *data)
{
	if(ft_init_mlx_map(data)==-1)
		return (ft_clean(data,0), -1);
	if(ft_init_mlx_minimap(data)==-1)
		return (ft_clean(data,1), -1);
	if(ft_init_rays(data)==-1)
		return (ft_clean(data,2), -1);
	// if(ft_init_textures(data)==-1)
	// 	return (ft_clean(data,3), -1);
	data->player.mouse_l_p = -1;
	return (0);
}



//----------------------------------------------
//------------------------------ Main :
//----------------------------------------------

int	ft_start(t_data *data)
{
	if (ft_init_game(data) == -1)
		return (-1);
		
	// struct timeval tv;
	// gettimeofday(&tv, NULL);
	// data->init_time = tv.tv_sec;
	// data->fps = 0;

	ft_hooks(data);
	mlx_loop_hook(data->mlx.ptr, ft_all, (void *)data);
	mlx_loop(data->mlx.ptr);
	
	return (ft_clean(data,4), 0);
}















































































































































































//----------------------------------------------
//------------------------------ minimap :
//----------------------------------------------

// void ft_init_minimap(t_data *data)
// {
// 	data->mini.mini_w=WIDTH / 6;
// 	data->mini.mini_h=HEIGHT / 4;
// 	data->mini.m_cell_size=(int)fmin(data->mini.mini_h / data->map.grid_y,data->mini.mini_w / data->map.grid_x);
// 	data->player.m_player_size = (int)fmax(data->mini.m_cell_size / 8, 4);
// 	data->player.mouse_l_p=-1.0;
// }

// void	ft_clear_minimap(data)
// {
// }

// void	ft_draw_minimap2(data)
// {
// }

// void	ft_draw_player_minimap(data)
// {
// }

// void ft_draw_minimap(t_data *data)
// {
// 	ft_init_minimap(data);
// 	ft_clear_minimap(data);
// 	ft_draw_minimap2(data);
// 	ft_draw_player_minimap(data);
// }


// //----------------


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



// // 1. Clear minimap :

//     for (int y = 0; y < mini_h; ++y)
//         for (int x = 0; x < mini_w; ++x)
//             mlx_put_pixel(data->mini.ptr_img, x, y, 0x000000FF);



// //  2. Compute visible map area (player at centre) :
//     float player_map_x = data->player.pos_x;
//     float player_map_y = data->player.pos_y;

//     float visible_cells_x = mini_w / (2.0f * scale);
//     float visible_cells_y = mini_h / (2.0f * scale);

//     int start_x = (int)(player_map_x - visible_cells_x);
//     int start_y = (int)(player_map_y - visible_cells_y);
//     int end_x   = (int)(player_map_x + visible_cells_x) + 1;
//     int end_y   = (int)(player_map_y + visible_cells_y) + 1;



// // 3. Draw solid map cells (your colors, no lines)  :
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



// // 4. Draw player (red square + white dot)  :
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



// // 5. Draw direction ray (yellow)           :
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
