/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/10/25 21:40:44 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_cell_size(int h, int w)
{
	return (fmin(HEIGHT / h, WIDTH / w));
}

void	ft_capture_keys(t_data *data)
{
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx.ptr);
}

int	ft_if_valid_move(t_data *data, int x, int y)
{
	if (x < 0 || x >= data->map.width)
		return (0);
	if (y < 0 || y >= data->map.height)
		return (0);
	if (data->map.grid[y][x] == '1')
		return (0);
	return (1);
}

void	ft_capture_player_moves(t_data *data)
{
	double	i;
	double	y;
	double	r;

	r = 0.1;
	i = data->player.pos_x;
	y = data->player.pos_y;
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_W))
	{
		if (ft_if_valid_move(data, (int)i, (int)(y - r)) == 1)
			data->player.pos_y -= r;
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_S))
	{
		if (ft_if_valid_move(data, (int)i, (int)(y + r)) == 1)
			data->player.pos_y += r;
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_D))
	{
		if (ft_if_valid_move(data, (int)(i + r), (int)y) == 1)
			data->player.pos_x += r;
	}
	if (mlx_is_key_down(data->mlx.ptr, MLX_KEY_A))
	{
		if (ft_if_valid_move(data, (int)(i - r), (int)y) == 1)
			data->player.pos_x -= r;
	}
}

void	ft_draw_map_2d(t_data *data, int i, int j, int s_square)
{
	int(y), (px), (py), x = -1;
	while (++x < data->map.width)
	{
		y = -1;
		while (++y < data->map.height)
		{
			i = -1;
			while (++i < s_square)
			{
				j = -1;
				while (++j < s_square)
				{
					px = x * s_square + j;
					py = y * s_square + i;
					if (data->map.grid[y][x] == '1')
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0x350707A1);
					else
						mlx_put_pixel(data->mlx.ptr_img, px, py, 0xF5DEB388);
				}
			}
		}
	}
}

void	ft_draw_player_2d(t_data *data, int px, int py, int s_square)
{
	int(n), (player_px), (player_py), (j), i = 0;
	n = fmax(s_square / 8, 2);
	player_px = data->player.pos_x * s_square - n;
	player_py = data->player.pos_y * s_square - n;
	i = 0;
	while (i < n * 2)
	{
		j = 0;
		while (j < n * 2)
		{
			px = player_px + j;
			py = player_py + i;
			mlx_put_pixel(data->mlx.ptr_img, px, py, 0x000000);
			j++;
		}
		i++;
	}
	mlx_put_pixel(data->mlx.ptr_img, player_px + n, player_py + n, 0xFFFFFF);
}

void	ft_all(void *param)
{
	int		s_square;
	t_data	*data;

	data = (t_data *)param;
	s_square = ft_cell_size(data->map.height, data->map.width);
	ft_capture_keys(data);
	ft_draw_map_2d(data, 0, 0, s_square);
	ft_capture_player_moves(data);
	ft_draw_player_2d(data, 0, 0, s_square);
	// ft_draw_rays(data);
}

int	ft_start(t_data *data)
{
	data->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!data->mlx.ptr)
		return (-1);
	data->mlx.ptr_img = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	if (!data->mlx.ptr_img)
		return (-1);
	data->mlx.idx = mlx_image_to_window(data->mlx.ptr, data->mlx.ptr_img, 0, 0);
	if (data->mlx.idx == -1)
		return (-1);
	mlx_loop_hook(data->mlx.ptr, ft_all, (void *)data);
	mlx_loop(data->mlx.ptr);
	mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
	mlx_terminate(data->mlx.ptr);
	return (0);
}
