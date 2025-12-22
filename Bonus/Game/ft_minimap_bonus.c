/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:06:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/21 17:44:26 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

uint32_t	get_minimap_color(char c)
{
	if (c == '1')
		return (0x350707FF);
	if (c == '0' || c == '3' || is_player_char(c))
		return (0xF5DEB3FF);
	if (c == '2')
		return (0xc71a1aFF);
	if (c == '4' || c == '5')
		return (0x3b0b84FF);
	return (0x000000FF);
}

void	ft_draw_cells(t_data *data, t_norm tmp, char c)
{
	int	px;
	int	py;

	py = 0;
	while (py < data->mini.cell_size)
	{
		px = 0;
		while (px < data->mini.cell_size)
		{
			put_px(data->mini.ptr_img, px + tmp.px, py + tmp.py,
				get_minimap_color(c));
			px++;
		}
		py++;
	}
}

void	ft_draw_map(t_data *data)
{
	t_norm	tmp;

	tmp.i = (data->mini.height / data->mini.cell_size) / 2;
	tmp.y_s = (int)data->player.pos_y - tmp.i;
	tmp.y_e = (int)data->player.pos_y + tmp.i;
	tmp.py = 0;
	while (tmp.y_s < tmp.y_e)
	{
		tmp.j = (data->mini.width / data->mini.cell_size) / 2;
		tmp.x_s = (int)data->player.pos_x - tmp.j;
		tmp.x_e = (int)data->player.pos_x + tmp.j;
		tmp.px = 0;
		while (tmp.x_s < tmp.x_e)
		{
			ft_draw_cells(data, tmp, get_char_at(data, tmp.y_s, tmp.x_s));
			tmp.px += data->mini.cell_size;
			tmp.x_s++;
		}
		tmp.py += data->mini.cell_size;
		tmp.y_s++;
	}
}

void	ft_draw_player(t_data *data)
{
	t_norm	tmp;

	tmp.x_s = data->mini.width / 2;
	tmp.y_s = data->mini.height / 2;
	tmp.p_size = data->mini.p_size / 2;
	tmp.py = tmp.y_s - tmp.p_size;
	while (tmp.py < tmp.y_s + tmp.p_size)
	{
		tmp.px = tmp.x_s - tmp.p_size;
		while (tmp.px < tmp.x_s + tmp.p_size)
		{
			put_px(data->mini.ptr_img, tmp.px, tmp.py, 0x000000FF);
			tmp.px++;
		}
		tmp.py++;
	}
}

void	ft_minimap(t_data *data)
{
	if (!data->mini.ptr_img)
		return ;
	ft_draw_map(data);
	ft_draw_player(data);
}

void	ft_draw_big_map_cells(mlx_image_t *img, t_norm tmp, char c, int cell_s)
{
	int	px;
	int	py;

	py = 0;
	while (py < cell_s)
	{
		px = 0;
		while (px < cell_s)
		{
			put_px(img, px + tmp.px, py + tmp.py, get_minimap_color(c));
			px++;
		}
		py++;
	}
}

void	ft_draw_big_map_player(mlx_image_t *img, t_norm tmp, int p_size)
{
	int	px;
	int	py;

	py = tmp.y_s - p_size / 2;
	while (py < tmp.y_s + p_size / 2)
	{
		px = tmp.x_s - p_size / 2;
		while (px < tmp.x_s + p_size / 2)
		{
			put_px(img, px, py, 0x000000FF);
			px++;
		}
		py++;
	}
}

void	ft_draw_full_map(t_game *game, t_data *data, mlx_image_t *img)
{
	t_norm	tmp;
	int		cell_size;

	(void)game;
	cell_size = 40;
	tmp.i = (HEIGHT / cell_size) / 2;
	tmp.y_s = (int)data->player.pos_y - tmp.i;
	tmp.y_e = (int)data->player.pos_y + tmp.i;
	tmp.py = 0;
	while (tmp.y_s < tmp.y_e)
	{
		tmp.j = (WIDTH / cell_size) / 2;
		tmp.x_s = (int)data->player.pos_x - tmp.j;
		tmp.x_e = (int)data->player.pos_x + tmp.j;
		tmp.px = 0;
		while (tmp.x_s < tmp.x_e)
		{
			ft_draw_big_map_cells(img, tmp, get_char_at(data, tmp.y_s,
					tmp.x_s), cell_size);
			tmp.px += cell_size;
			tmp.x_s++;
		}
		tmp.py += cell_size;
		tmp.y_s++;
	}
	tmp.x_s = WIDTH / 2;
	tmp.y_s = HEIGHT / 2;
	ft_draw_big_map_player(img, tmp, 16);
}

void	ft_big_map(t_game *game, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_px(game->mlx.ptr_img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	ft_draw_full_map(game, data, game->mlx.ptr_img);
}
