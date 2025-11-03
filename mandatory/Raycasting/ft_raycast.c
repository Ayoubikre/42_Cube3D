/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/11/03 11:34:12 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//----------------------------------------------
//------------------------------ extra :
//----------------------------------------------

double	ft_rad(double x)
{
	return (x * M_PI / 180.0);
}

double	ft_deg(double x)
{
	return (x * 180.0 / M_PI);
}

//----------------------------------------------
//------------------------------ keys :
//----------------------------------------------

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	(void)keydata;
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
//------------------------------ get colores:
//----------------------------------------------

unsigned int	ft_color(t_color clr)
{
	return (clr.r << 16 | clr.g << 8 | clr.b);
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
						mlx_put_pixel(data->mlx.ptr_img, px, py,
							ft_color(data->ceiling_color));
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py,
							ft_color(data->floor_color));
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
            break ;
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

void	ft_init_ray_data(t_data *data, int i, double r)
{
	RAY(i).angle = (ANG - (FOV / 2)) + (i * r);
	if (RAY(i).angle < 0)
		RAY(i).angle += 2 * M_PI;
	else if (RAY(i).angle >= 2 * M_PI)
		RAY(i).angle -= 2 * M_PI;
	RAY(i).ang_cos = cos(RAY(i).angle);
	RAY(i).const_x = fabs(CELL_S / RAY(i).ang_cos);
	RAY(i).x = floor(data->player.pos_x);
	RAY(i).ang_sin = sin(RAY(i).angle);
	RAY(i).const_y = fabs(CELL_S / RAY(i).ang_sin);
	RAY(i).y = floor(data->player.pos_y);
	RAY(i).hit = 0;
}

void	ft_first_cell_len(t_data *data, int i)
{
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
}

void	ft_dda(t_data *data, int i)
{
	while (RAY(i).hit == 0)
	{
		if (RAY(i).extra_x < RAY(i).extra_y)
		{
			RAY(i).extra_x += RAY(i).const_x;
			RAY(i).x += RAY(i).step_x;
			RAY(i).side = 0;
			RAY(i).len = (RAY(i).x - data->player.pos_x + (1 - RAY(i).step_x)
				/ 2) / RAY(i).ang_cos;
		}
		else
		{
			RAY(i).extra_y += RAY(i).const_y;
			RAY(i).y += RAY(i).step_y;
			RAY(i).side = 1;
			RAY(i).len = (RAY(i).y - data->player.pos_y + (1 - RAY(i).step_y)
				/ 2) / RAY(i).ang_sin;
		}
		if (data->map.grid[RAY(i).y][RAY(i).x] == '1')
			RAY(i).hit = 1;
	}
}

void	ft_raycasting(t_data *data)
{
	int		i;
	double	r;

	i = -1;
	FOV = RAD(90);
	r = FOV / RAYS;
	while (++i < RAYS)
	{
		ft_init_ray_data(data, i, r);
		ft_first_cell_len(data, i);
		ft_dda(data, i);
		ft_draw_ray(data, RAY(i).angle, 1, RAY(i).len);
	}
	ft_draw_ray(data, ANG, 0, 50);
	ft_draw_ray(data, ANG - (FOV / 2), 0, 50);
	ft_draw_ray(data, ANG + (FOV / 2), 0, 50);
}

//----------------------------------------------
//------------------------------ clean :
//----------------------------------------------

void	ft_clean(t_data *data, int f)
{
	if (f >= 0)
		mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
	if (f >= 1)
		mlx_delete_image(data->mlx.ptr, data->mini.ptr_img);
	if (f >= 2)
		free(data->rays);
	// if(f>=3)
	// {
	// }
	mlx_terminate(data->mlx.ptr);
}

//----------------------------------------------
//------------------------------ the Engine :
//----------------------------------------------

void	ft_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_draw_background(data, 0, 0);
	ft_draw_map_2d(data, 0, 0);
	ft_capture_player_moves(data);
	ft_draw_player_2d(data, 0, 0);
	ft_raycasting(data);
}

//----------------------------------------------
//------------------------------ hooks :
//----------------------------------------------

void	ft_hooks(t_data *data)
{
	mlx_key_hook(data->mlx.ptr, ft_capture_keys, (void *)data);
	mlx_cursor_hook(data->mlx.ptr, ft_update_mouse_angle, (void *)data);
	mlx_set_cursor_mode(data->mlx.ptr, MLX_MOUSE_DISABLED);
}

//----------------------------------------------
//------------------------------ init :
//----------------------------------------------

int	ft_init_mlx_map(t_data *data)
{
	data->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!data->mlx.ptr)
		return (-1);
	data->mlx.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	if (!data->mlx.ptr_img)
		return (-1);
	data->mlx.id_img = mlx_image_to_window(data->mlx.ptr, data->mlx.ptr_img, 0,
			0);
	if (data->mlx.id_img == -1)
		return (-1);
	CELL_S = (int)fmin(HEIGHT / data->map.grid_y, WIDTH / data->map.grid_x);
	return (0);
}

int	ft_init_mlx_minimap(t_data *data)
{
	data->mini.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH / 5, HEIGHT / 3);
	if (!data->mini.ptr_img)
		return (-1);
	data->mini.id_img = mlx_image_to_window(data->mlx.ptr, data->mini.ptr_img,
			10, 10);
	if (data->mini.id_img == -1)
		return (-1);
	return (0);
}

int	ft_init_rays(t_data *data)
{
	data->rays = malloc(sizeof(t_ray) * RAYS);
	if (!data->rays)
		return (-1);
	ft_memset(data->rays, 0, sizeof(t_ray) * RAYS);
	return (0);
}

int	ft_init_game(t_data *data)
{
	if (ft_init_mlx_map(data) == -1)
		return (ft_clean(data, 0), -1);
	if (ft_init_mlx_minimap(data) == -1)
		return (ft_clean(data, 1), -1);
	if (ft_init_rays(data) == -1)
		return (ft_clean(data, 2), -1);
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
	ft_hooks(data);
	mlx_loop_hook(data->mlx.ptr, ft_all, (void *)data);
	mlx_loop(data->mlx.ptr);
	return (ft_clean(data, 4), 0);
}
