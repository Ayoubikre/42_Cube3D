/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 06:39:19 by akzaza            #+#    #+#             */
/*   Updated: 2025/10/19 07:30:05 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	handle_map_error(char *line, char *error_msg)
{
	free(line);
	print_error(error_msg);
	return (0);
}

int	map_exists(t_data *data, char *line)
{
	if (is_element_line(line))
		return (handle_map_error(line, "Element identifier found inside map"));
	if (is_empty_line(line))
		return (handle_map_error(line, "Empty line found inside map"));
	if (!is_map_line(line))
		return (handle_map_error(line, "Invalid character in map"));
	if (!store_map_line(data, line))
	{
		free(line);
		return (0);
	}
	return (1);
}

static int	handle_non_map_line(char *line, t_data *data, int *map_started)
{
	if (is_empty_line(line))
		return (1);
	if (!is_map_line(line))
		return (handle_map_error(line, "Invalid line after elements"));
	if (!store_map_line(data, line))
	{
		free(line);
		return (0);
	}
	*map_started = 1;
	return (1);
}

int	parse_map(int fd, t_data *data, char *first_line)
{
	char	*line;
	int		map_started;

	map_started = 0;
	if (first_line && !is_empty_line(first_line))
	{
		if (!store_map_line(data, first_line))
			return (0);
		map_started = 1;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (map_started && !map_exists(data, line))
			return (0);
		if (!map_started && !handle_non_map_line(line, data, &map_started))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_started || data->map.height == 0)
		return (handle_map_error(NULL, "No valid map found"));
	return (1);
}

int	check_map_characters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			if (!is_map_char(data->map.grid[i][j]))
			{
				print_error("Invalid character in map");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
