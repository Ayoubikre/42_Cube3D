/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:57:21 by noctis            #+#    #+#             */
/*   Updated: 2025/12/05 02:42:42 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	t_data	*data;

	(void)keydata;
	game = (t_game *)param;
	data = &game->c_lvl->data;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx.ptr);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_F))
	{
		ft_open_and_close_doors(data, 0);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_V))
	{
		ft_switch_lvl(game, data);
	}
}

void	ft_open_and_close_doors(t_data *data, int f)
{
	int (x), (y), (dff_x), (dff_y);
	if (f)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			x = -1;
			while (++x < (int)ft_strlen(data->map.grid[y]))
			{
				if (data->map.grid[y][x] != '3')
					continue ;
				dff_x = (int)(data->player.pos_x) - x;
				dff_y = (int)(data->player.pos_y) - y;
				if (dff_x >= -2 && dff_x <= 2 && dff_y >= -2 && dff_y <= 2)
					continue ;
				data->map.grid[y][x] = '2';
			}
		}
	}
	else
	{
		if (data->rays[RAYS / 2].len <= 2.0 && data->rays[RAYS / 2].hit == 2)
			data->map.grid[data->rays[RAYS / 2].y][data->rays[RAYS
				/ 2].x] = '3';
	}
}
