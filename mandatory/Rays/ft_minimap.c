/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:06:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/05 02:53:13 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_within_circle(t_data *data, int x, int y)
{
	int	center_x;
	int	center_y;
	int	dx;
	int	dy;

	center_x = data->mini.mini_w / 2;
	center_y = data->mini.mini_h / 2;
	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= data->mini.radius * data->mini.radius);
}

static void	draw_minimap_cell(t_game *game, t_data *data, int screen_x,
		int screen_y, char cell)
{
	int			px;
	int			py;
	uint32_t	color;

	if (cell == '1')
		color = 0x808080FF;
	else if (cell == '0' || is_player_char(cell))
		color = 0xFFFFFFFF;
	else if (cell == '2')
		color = 0xFF0000FF;
	else if (cell == '4')
		color = 0x00FF00FF;
	else
		color = 0x000000FF;
	py = 0;
	while (py < data->mini.m_cell_size)
	{
		px = 0;
		while (px < data->mini.m_cell_size)
		{
			if (is_within_circle(data, screen_x + px, screen_y + py))
				put_px(data->mini.ptr_img, screen_x + px, screen_y + py, color);
			px++;
		}
		py++;
	}
}

static void	calculate_minimap_bounds(t_data *data, int *start_x, int *start_y,
		int *end_x, int *end_y)
{
	int	cells_x;
	int	cells_y;

	cells_x = data->mini.mini_w / data->mini.m_cell_size;
	cells_y = data->mini.mini_h / data->mini.m_cell_size;
	*start_x = (int)data->player.pos_x - cells_x / 2;
	*start_y = (int)data->player.pos_y - cells_y / 2;
	*end_x = *start_x + cells_x;
	*end_y = *start_y + cells_y;
}

static void	draw_minimap_grid(t_game *game, t_data *data)
{
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		map_x;
	int		map_y;
	int		screen_x;
	int		screen_y;
	char	cell;

	calculate_minimap_bounds(data, &start_x, &start_y, &end_x, &end_y);
	map_y = start_y;
	screen_y = 0;
	while (map_y < end_y && screen_y < (int)data->mini.mini_h)
	{
		map_x = start_x;
		screen_x = 0;
		while (map_x < end_x && screen_x < (int)data->mini.mini_w)
		{
			cell = get_char_at(data, map_y, map_x);
			draw_minimap_cell(game, data, screen_x, screen_y, cell);
			screen_x += data->mini.m_cell_size;
			map_x++;
		}
		screen_y += data->mini.m_cell_size;
		map_y++;
	}
}

static void	draw_player_point(t_game *game, t_data *data)
{
	int	center_x;
	int	center_y;
	int	px;
	int	py;
	int	half_size;

	center_x = data->mini.mini_w / 2;
	center_y = data->mini.mini_h / 2;
	half_size = data->mini.m_player_size / 2;
	py = center_y - half_size;
	while (py < center_y + half_size)
	{
		px = center_x - half_size;
		while (px < center_x + half_size)
		{
			if (is_within_circle(data, px, py))
				put_px(data->mini.ptr_img, px, py, 0x000000FF);
			px++;
		}
		py++;
	}
}

void	ft_minimap(t_game *game, t_data *data)
{
	if (!data->mini.ptr_img)
		return ;
	draw_minimap_grid(game, data);
	draw_player_point(game, data);
}
