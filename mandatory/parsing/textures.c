/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 07:34:36 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/19 14:52:31 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

int	get_texture_index(char *identifier, int *text, int *elemt)
{
	if (ft_strncmp(identifier, "NO", 2) == 0 && \
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
		return ((*text = NORTH), (*elemt = ELEM_NO), 1);
	else if (ft_strncmp(identifier, "SO", 2) == 0 && \
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
		return ((*text = SOUTH), (*elemt = ELEM_SO), 1);
	else if (ft_strncmp(identifier, "WE", 2) == 0 && \
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
		return ((*text = WEST), (*elemt = ELEM_WE), 1);
	else if (ft_strncmp(identifier, "EA", 2) == 0 && \
		(identifier[2] == '\0' || ft_isspace(identifier[2])))
		return ((*text = EAST), (*elemt = ELEM_EA), 1);
	return (0);
}

char	*extract_texture_path(char *line)
{
	char	*path;
	char	*start;
	char	*end;

	start = skip_spaces(line);
	if (!start || !*start)
		return (NULL);
	end = start;
	while (*end && *end != '\n' && *end != '\r')
		end++;
	end--;
	while (end > start && ft_isspace(*end))
		end--;
	end++;
	path = ft_substr(start, 0, end - start);
	if (!path)
		return (NULL);
	return (path);
}

int	set_texture(t_data *data, int tex_idx, int elem_idx, char *path)
{
	if (data->parsed[elem_idx])
	{
		free(path);
		print_error("Duplicate texture identifier");
		return (0);
	}
	if (!check_file(path, 3))
	{
		free(path);
		print_error("Texture file does not exist or is not readable");
		return (0);
	}
	data->textures[tex_idx] = path;
	data->parsed[elem_idx] = 1;
	return (1);
}

int	parse_texture_line(char *line, t_data *data)
{
	char	*identifier;
	char	*path;
	int		tex_idx;
	int		elem_idx;

	if (!line || !data)
		return (0);
	identifier = skip_spaces(line);
	if (!identifier || !*identifier)
		return (0);
	if (!get_texture_index(identifier, &tex_idx, &elem_idx))
		return (0);
	identifier += 2;
	identifier = skip_spaces(identifier);
	path = extract_texture_path(identifier);
	if (!path)
	{
		print_error("Invalid texture path");
		return (0);
	}
	return (set_texture(data, tex_idx, elem_idx, path));
}
