/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:28:05 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 19:38:35 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_capture_big_map_moves(t_game *game, t_data *data)
{
	double	map_speed;

	map_speed = 0.5;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_UP))
		data->big.offset_y -= map_speed;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_DOWN))
		data->big.offset_y += map_speed;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_LEFT))
		data->big.offset_x -= map_speed;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_RIGHT))
		data->big.offset_x += map_speed;
}

void	ft_draw_cells_large(t_data *data, t_norm tmp, char c)
{
	int	px;
	int	py;

	py = 0;
	while (py < data->big.cell_size)
	{
		px = 0;
		while (px < data->big.cell_size)
		{
			put_px(data->big.ptr_img, px + tmp.px, py + tmp.py,
				get_minimap_color(c));
			px++;
		}
		py++;
	}
}

void	ft_draw_player_marker(t_data *data, t_norm tmp)
{
	int	px;
	int	py;
	int	half;

	half = data->big.p_size / 2;
	py = (data->big.cell_size / 2) - half;
	while (py < (data->big.cell_size / 2) + half)
	{
		px = (data->big.cell_size / 2) - half;
		while (px < (data->big.cell_size / 2) + half)
		{
			put_px(data->big.ptr_img, px + tmp.px, py + tmp.py, 0x000000FF);
			px++;
		}
		py++;
	}
}

void	ft_draw_map_large(t_data *data)
{
	t_norm	tmp;

	tmp.i = (data->big.height / data->big.cell_size) / 2;
	tmp.y_s = (int)data->player.pos_y - tmp.i + data->big.offset_y;
	tmp.y_e = (int)data->player.pos_y + tmp.i + data->big.offset_y;
	tmp.py = 0;
	while (tmp.y_s < tmp.y_e)
	{
		tmp.j = (data->big.width / data->big.cell_size) / 2;
		tmp.x_s = (int)data->player.pos_x - tmp.j + data->big.offset_x;
		tmp.x_e = (int)data->player.pos_x + tmp.j + data->big.offset_x;
		tmp.px = 0;
		while (tmp.x_s < tmp.x_e)
		{
			ft_draw_cells_large(data, tmp, get_char_at(data, tmp.y_s, tmp.x_s));
			if ((int)data->player.pos_x == tmp.x_s
				&& (int)data->player.pos_y == tmp.y_s)
				ft_draw_player_marker(data, tmp);
			tmp.px += data->big.cell_size;
			tmp.x_s++;
		}
		tmp.py += data->big.cell_size;
		tmp.y_s++;
	}
}

int	ft_map(t_game *game, t_data *data, int x, int y)
{
	if (!game->show_map || !data->big.ptr_img)
		return (0);
	while (++y < data->big.height)
	{
		x = -1;
		while (++x < data->big.width)
			put_px(data->big.ptr_img, x, y, 0x000000FF);
	}
	ft_capture_big_map_moves(game, data);
	ft_draw_map_large(data);
	return (1);
}
