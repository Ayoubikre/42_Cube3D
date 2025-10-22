/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:44:11 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/19 14:50:51 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || \
		c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	element_line(char *line, t_data *data)
{
	if (is_element_line(line))
	{
		if (is_texture_line(line))
		{
			if (!parse_texture_line(line, data))
				return ((free(line)), 0);
		}
		else
		{
			if (!parse_color_line(line, data))
				return ((free(line)), 0);
		}
	}
	else
	{
		free(line);
		print_error("Invalid line in file");
		return (0);
	}
	return (1);
}

int	parse_elements(int fd, t_data *data, char **first_map_line)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_map_line(line))
		{
			*first_map_line = line;
			return (1);
		}
		if (!element_line(line, data))
			return (0);
		free(line);
		line = get_next_line(fd);
	}
	print_error("No map found in file");
	return (0);
}

void	frr(int fd, char *str)
{
	free(str);
	close(fd);
}

int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*first_mline;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ((print_error("Cannot open file")), 0);
	first_mline = NULL;
	if (!parse_elements(fd, data, &first_mline))
		return ((close(fd)), 0);
	if (!validate_elements_complete(data))
		return ((frr(fd, first_mline)), 0);
	if (!parse_map(fd, data, first_mline))
		return ((frr(fd, first_mline)), 0);
	frr(fd, first_mline);
	if (!validate_map(data))
		return (0);
	return (1);
}
