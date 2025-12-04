/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:35 by akzaza            #+#    #+#             */
/*   Updated: 2025/12/04 03:33:41 by noctis           ###   ########.fr       */
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
	if (data->player.orientation == 'E')
		data->ang = ft_rad(0);
	if (data->player.orientation == 'S')
		data->ang = ft_rad(90);
	if (data->player.orientation == 'W')
		data->ang = ft_rad(180);
	if (data->player.orientation == 'N')
		data->ang = ft_rad(270);
}

char	get_char_at(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map.grid_y)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map.grid[y]))
		return (' ');
	return (data->map.grid[y][x]);
}

static int	check_surrounded(t_data *data, int y, int x)
{
	char	c;

	c = get_char_at(data, y - 1, x);
	if (!is_valid_pos(c))
		return (0);
	c = get_char_at(data, y + 1, x);
	if (!is_valid_pos(c))
		return (0);
	c = get_char_at(data, y, x - 1);
	if (!is_valid_pos(c))
		return (0);
	c = get_char_at(data, y, x + 1);
	if (!is_valid_pos(c))
		return (0);
	return (1);
}

int	check_map_closed(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->map.grid_y)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			c = data->map.grid[i][j];
			if (c == '0' || c == '2' || c == '4' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W')
			{
				if (!check_surrounded(data, i, j))
					return ((print_error("Map not closed (space or \
						void near walkable area)")),
						0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
