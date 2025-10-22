/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:49:54 by akzaza            #+#    #+#             */
/*   Updated: 2025/10/19 07:34:18 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*trim_newline(char *line)
{
	int		len;
	char	*trimmed;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > 0 && line[len - 1] == '\r')
		len--;
	trimmed = ft_substr(line, 0, len);
	return (trimmed);
}

static char	**realloc_grid(char **old_grid, int old_height, int new_height)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (new_height + 1));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < old_height)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	new_grid[new_height - 1] = NULL;
	new_grid[new_height] = NULL;
	if (old_grid)
		free(old_grid);
	return (new_grid);
}

int	store_map_line(t_data *data, char *line)
{
	char	*trimmed;
	int		line_len;

	if (!line || !data)
		return (0);
	trimmed = trim_newline(line);
	if (!trimmed)
	{
		print_error("Memory allocation failed");
		return (0);
	}
	line_len = ft_strlen(trimmed);
	if (line_len > data->map.width)
		data->map.width = line_len;
	data->map.grid = realloc_grid(data->map.grid, data->map.height, \
		data->map.height + 1);
	if (!data->map.grid)
	{
		free(trimmed);
		print_error("Memory allocation failed");
		return (0);
	}
	data->map.grid[data->map.height] = trimmed;
	data->map.height++;
	return (1);
}

int	find_player(t_data *data)
{
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (data->map.grid[i][++j])
		{
			if (is_player_char(data->map.grid[i][j]))
			{
				player_count++;
				set_player_data(data, i, j);
			}
		}
	}
	if (player_count == 0)
		return ((print_error("No player found in map")), 0);
	if (player_count > 1)
		return ((print_error("Multiple players found in map")), 0);
	return (1);
}

int	validate_map(t_data *data)
{
	if (!data || !data->map.grid)
	{
		print_error("No map data");
		return (0);
	}
	if (data->map.height == 0 || data->map.width == 0)
	{
		print_error("Empty map");
		return (0);
	}
	if (!check_map_characters(data))
		return (0);
	if (!find_player(data))
		return (0);
	if (!check_map_closed(data))
		return (0);
	return (1);
}
