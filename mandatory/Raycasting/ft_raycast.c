/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/11/03 14:16:48 by noctis           ###   ########.fr       */
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
	data->ang += new_x * MOUSE_SP;
	if (data->ang < 0)
		data->ang += 2 * M_PI;
	else if (data->ang >= 2 * M_PI)
		data->ang -= 2 * M_PI;
}

int	ft_find_walls(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.grid_x)
		return (1);
	if (y < 0 || y >= data->map.grid_y)
		return (1);
	if (data->map.grid[y][x] == '1' || data->map.grid[y][x] == '2')
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
		ft_move(data, cos(data->ang), sin(data->ang), 0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
	{
		ft_move(data, -cos(data->ang), -sin(data->ang), 0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
	{
		ft_move(data, cos(data->ang + M_PI / 2), sin(data->ang + M_PI / 2),
			0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
	{
		ft_move(data, cos(data->ang - M_PI / 2), sin(data->ang - M_PI / 2),
			0.1);
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_LEFT))
	{
		data->ang -= ft_rad(2);
		if (data->ang < 0)
			data->ang += 2 * M_PI;
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_RIGHT))
	{
		data->ang += ft_rad(2);
		if (data->ang >= 2 * M_PI)
			data->ang -= 2 * M_PI;
	}}

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
	s = (int)fmax(data->map.cell_s / 8, 4);
	player_px = data->player.pos_x * data->map.cell_s;
	player_py = data->player.pos_y * data->map.cell_s;
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
			while (++i < data->map.cell_s)
			{
				j = -1;
				while (++j < data->map.cell_s)
				{
					px = x * data->map.cell_s + i;
					py = y * data->map.cell_s + j;
					if (data->map.grid[y][x] == '1')
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x350707A1);
					else if (data->map.grid[y][x] == '2')
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xA507A7A1);
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
			while (++i < data->map.cell_s)
			{
				j = -1;
				while (++j < data->map.cell_s)
				{
					px = x * data->map.cell_s + i;
					py = y * data->map.cell_s + j;
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

void	ft_draw_ray(t_data *data, double angle, double ray_len)
{
    int x0 = (int)((data->player.pos_x * data->map.cell_s)) ;
    int y0 = (int)((data->player.pos_y * data->map.cell_s));
    double len_in_pixels = (ray_len ) * data->map.cell_s;
	int	x1 = (int)(x0 + cos(angle) * len_in_pixels);
	int	y1 = (int)(y0 + sin(angle) * len_in_pixels);
    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;
    while (1)
    {
		mlx_put_pixel(data->mlx.ptr_img, x0, y0, 0x500075FF);
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

void	ft_init_ray_data(t_data *data, t_ray *ray, int i, double r)
{
	ray->angle = (data->ang - (data->fov / 2)) + (i * r);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	else if (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
	ray->ang_cos = cos(ray->angle);
	ray->const_x = fabs(data->map.cell_s / ray->ang_cos);
	ray->x = floor(data->player.pos_x);
	ray->ang_sin = sin(ray->angle);
	ray->const_y = fabs(data->map.cell_s / ray->ang_sin);
	ray->y = floor(data->player.pos_y);
	ray->hit = 0;
}

void	ft_first_cell_len(t_data *data, t_ray *ray)
{
	if (ray->ang_cos < 0)
	{
		ray->step_x = -1;
		ray->extra_x = (data->player.pos_x - ray->x) * ray->const_x;
	}
	else
	{
		ray->step_x = 1;
		ray->extra_x = (ray->x + 1.0 - data->player.pos_x) * ray->const_x;
	}
	if (ray->ang_sin < 0)
	{
		ray->step_y = -1;
		ray->extra_y = (data->player.pos_y - ray->y) * ray->const_y;
	}
	else
	{
		ray->step_y = 1;
		ray->extra_y = (ray->y + 1.0 - data->player.pos_y) * ray->const_y;
	}
}

void	ft_dda(t_data *data, t_ray *ray)
{
	char	w;

	while (ray->hit == 0)
	{
		if (ray->extra_x < ray->extra_y)
		{
			ray->extra_x += ray->const_x;
			ray->x += ray->step_x;
			ray->side = 0;
			ray->len = (ray->x - data->player.pos_x + (1 - ray->step_x) / 2)
				/ ray->ang_cos;
		}
		else
		{
			ray->extra_y += ray->const_y;
			ray->y += ray->step_y;
			ray->side = 1;
			ray->len = (ray->y - data->player.pos_y + (1 - ray->step_y) / 2)
				/ ray->ang_sin;
		}
		w = data->map.grid[ray->y][ray->x];
		if (w == '1' || w == '2')
			ray->hit = 1;
	}
}

void	ft_raycasting(t_data *data)
{
	int		i;
	double	r;

	i = -1;
	r = data->fov / RAYS;
	while (++i < RAYS)
	{
		ft_init_ray_data(data, &data->rays[i], i, r);
		ft_first_cell_len(data, &data->rays[i]);
		ft_dda(data, &data->rays[i]);
		ft_draw_ray(data, data->rays[i].angle, data->rays[i].len);
	}
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
	data->map.cell_s = (int)fmin(HEIGHT / data->map.grid_y, WIDTH
			/ data->map.grid_x);
	data->fov = ft_rad(90);
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
