/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 01:44:22 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/19 14:51:54 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_texture_line(char *line)
{
	char	*str;

	if (!line)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if ((ft_strncmp(str, "NO", 2) == 0 && (str[2] == '\0' \
	|| ft_isspace(str[2]))) || \
		(ft_strncmp(str, "SO", 2) == 0 && (str[2] == '\0' \
		|| ft_isspace(str[2]))) || \
		(ft_strncmp(str, "WE", 2) == 0 && (str[2] == '\0' \
		|| ft_isspace(str[2]))) || \
		(ft_strncmp(str, "EA", 2) == 0 && (str[2] == '\0' \
		|| ft_isspace(str[2]))))
		return (1);
	return (0);
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int		i;
	int		has_content;

	if (!line || is_empty_line(line))
		return (0);
	i = 0;
	has_content = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_content = 1;
		i++;
	}
	return (has_content);
}

int	is_element_line(char *line)
{
	char	*str;

	if (!line)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if ((ft_strncmp(str, "NO", 2) == 0 && \
	(str[2] == '\0' || ft_isspace(str[2]))) || \
		(ft_strncmp(str, "SO", 2) == 0 && \
		(str[2] == '\0' || ft_isspace(str[2]))) || \
		(ft_strncmp(str, "WE", 2) == 0 && \
		(str[2] == '\0' || ft_isspace(str[2]))) || \
		(ft_strncmp(str, "EA", 2) == 0 && \
		(str[2] == '\0' || ft_isspace(str[2]))))
		return (1);
	if ((str[0] == 'F' && (str[1] == '\0' || ft_isspace(str[1]))) || \
		(str[0] == 'C' && (str[1] == '\0' || ft_isspace(str[1]))))
		return (1);
	return (0);
}
