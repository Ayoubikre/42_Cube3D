/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:06:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/15 05:08:06 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	is_in_circle(int x, int y, int center_x, int center_y, int radius)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= radius * radius);
}

int	get_minimap_radius(t_data *data)
{
	if (data->mini.width < data->mini.height)
		return (data->mini.width / 2);
	return (data->mini.height / 2);
}

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
	return (0x000000A0);
}

void	ft_draw_cells(t_data *data, t_norm tmp, char c)
{
	int	px;
	int	py;
	int	center_x;
	int	center_y;
	int	radius;

	center_x = data->mini.width / 2;
	center_y = data->mini.height / 2;
	radius = get_minimap_radius(data);
	py = 0;
	while (py < data->mini.cell_size)
	{
		px = 0;
		while (px < data->mini.cell_size)
		{
			if (is_in_circle(px + tmp.px, py + tmp.py,
					center_x, center_y, radius))
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
	int		center_x;
	int		center_y;
	int		radius;

	center_x = data->mini.width / 2;
	center_y = data->mini.height / 2;
	radius = get_minimap_radius(data);
	tmp.x_s = center_x;
	tmp.y_s = center_y;
	tmp.p_size = data->mini.p_size / 2;
	tmp.py = tmp.y_s - tmp.p_size;
	while (tmp.py < tmp.y_s + tmp.p_size)
	{
		tmp.px = tmp.x_s - tmp.p_size;
		while (tmp.px < tmp.x_s + tmp.p_size)
		{
			if (is_in_circle(tmp.px, tmp.py, center_x, center_y, radius))
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
