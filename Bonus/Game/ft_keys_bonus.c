/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:57:21 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 19:19:46 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_capture_keys(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	t_data	*data;

	(void)keydata;
	game = (t_game *)param;
	data = &game->c_lvl->data;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx.ptr);
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_F))
	{
		ft_open_and_close_doors(data, 0);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_V))
	{
		ft_switch_lvl(game, data);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_L))
	{
		ft_lock_and_unlock_cam(game);
	}
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_M))
	{
		ft_show_and_hide_map(game, data);
	}
}

void	ft_toggle_mlx_imgs(t_game *game, t_data *data, bool x)
{
	{
		if (data->big.ptr_img)
		{
			data->big.ptr_img->enabled = !x;
		}
	}
	{
		if (game->mlx.ptr_img)
		{
			game->mlx.ptr_img->enabled = x;
		}
		if (game->hand.ptr_img)
		{
			game->hand.ptr_img->enabled = x;
		}
		if (data->mini.ptr_img)
		{
			data->mini.ptr_img->enabled = x;
		}
		if (data->mini.cadre_img)
		{
			data->mini.cadre_img->enabled = x;
		}
	}
}

void	ft_show_and_hide_map(t_game *game, t_data *data)
{
	data->big.offset_x = 0;
	data->big.offset_y = 0;
	if (game->show_map)
	{
		game->show_map = 0;
		ft_toggle_mlx_imgs(game, data, true);
	}
	else
	{
		game->show_map = 1;
		ft_toggle_mlx_imgs(game, data, false);
	}
}

void	ft_lock_and_unlock_cam(t_game *game)
{
	if (game->lock_cam == 0)
	{
		mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_NORMAL);
		game->lock_cam = 1;
	}
	else
	{
		mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_DISABLED);
		game->lock_cam = 0;
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
