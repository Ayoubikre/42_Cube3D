/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:35 by akzaza            #+#    #+#             */
/*   Updated: 2025/10/19 15:03:36 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_data(t_data *data, int i, int j)
{
	data->player.pos_x = j + 0.5;
	data->player.pos_y = i + 0.5;
	data->player.orientation = data->map.grid[i][j];
}

char	get_char_at(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map.height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map.grid[y]))
		return (' ');
	return (data->map.grid[y][x]);
}

static int	check_surrounded(t_data *data, int y, int x)
{
	char	c;
	int		dy;
	int		dx;

	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dy == 0 && dx == 0)
			{
				dx++;
				continue ;
			}
			c = get_char_at(data, y + dy, x + dx);
			if (!is_valid_pos(c))
				return ((print_error("Map not closed (space or \
void near walkable area)")), 0);
			dx++;
		}
		dy++;
	}
	return (1);
}

int	check_map_closed(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			c = data->map.grid[i][j];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!check_surrounded(data, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
