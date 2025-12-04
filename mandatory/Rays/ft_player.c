/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:58:46 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 01:57:08 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_speed(t_game *game, t_data *data)
{
	double	fov_max;
	double	sprint_speed;
	double	target_fov;
	double	target_speed;

	fov_max = ft_rad(120);
	sprint_speed = 0.50;
	target_fov = ft_rad(60);
	target_speed = 0.10;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_LEFT_SHIFT))
	{
		target_fov = fov_max;
		target_speed = sprint_speed;
	}
	data->fov += (target_fov - data->fov) * 0.05;
	if (data->fov > fov_max)
		data->fov = fov_max;
	data->move_speed += (target_speed - data->move_speed) * 0.05;
	if (data->move_speed > sprint_speed)
		data->move_speed = sprint_speed;
}

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
	if (data->map.grid[y][x] == '1' || data->map.grid[y][x] == '2'
		|| data->map.grid[y][x] == '4')
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

void	ft_capture_player_moves(t_game *game, t_data *data)
{
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_W))
	{
		ft_move(data, cos(data->ang), sin(data->ang), data->move_speed);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_S))
	{
		ft_move(data, -cos(data->ang), -sin(data->ang), data->move_speed);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_D))
	{
		ft_move(data, cos(data->ang + M_PI / 2), sin(data->ang + M_PI / 2),
			data->move_speed);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_A))
	{
		ft_move(data, cos(data->ang - M_PI / 2), sin(data->ang - M_PI / 2),
			data->move_speed);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_LEFT))
	{
		data->ang -= ft_rad(2);
		if (data->ang < 0)
			data->ang += 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_RIGHT))
	{
		data->ang += ft_rad(2);
		if (data->ang >= 2 * M_PI)
			data->ang -= 2 * M_PI;
	}
}
