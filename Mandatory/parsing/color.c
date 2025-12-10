/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 08:03:13 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/28 00:20:27 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_elements_complete(t_data *data)
{
	if (!all_elements_parsed(data))
	{
		if (!data->parsed[ELEM_NO])
			print_error("Missing North texture (NO)");
		else if (!data->parsed[ELEM_SO])
			print_error("Missing South texture (SO)");
		else if (!data->parsed[ELEM_WE])
			print_error("Missing West texture (WE)");
		else if (!data->parsed[ELEM_EA])
			print_error("Missing East texture (EA)");
		else if (!data->parsed[ELEM_F])
			print_error("Missing Floor color (F)");
		else if (!data->parsed[ELEM_C])
			print_error("Missing Ceiling color (C)");
		return (0);
	}
	return (1);
}

int	is_valid_pos(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == '4' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	parse_floor_color(char *line, t_data *data)
{
	char	*value_str;

	if (data->parsed[ELEM_F])
	{
		print_error("Duplicate floor color (F)");
		return (0);
	}
	value_str = skip_spaces(line + 1);
	if (!parse_rgb(value_str, &data->floor_color))
		return (0);
	data->parsed[ELEM_F] = 1;
	return (1);
}

int	parse_ceiling_color(char *line, t_data *data)
{
	char	*value_str;

	if (data->parsed[ELEM_C])
	{
		print_error("Duplicate ceiling color (C)");
		return (0);
	}
	value_str = skip_spaces(line + 1);
	if (!parse_rgb(value_str, &data->ceiling_color))
		return (0);
	data->parsed[ELEM_C] = 1;
	return (1);
}

int	parse_color_line(char *line, t_data *data)
{
	char	*str;

	if (!line || !data)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if (str[0] == 'F' && (str[1] == '\0' || ft_isspace(str[1])))
		return (parse_floor_color(str, data));
	else if (str[0] == 'C' && (str[1] == '\0' || ft_isspace(str[1])))
		return (parse_ceiling_color(str, data));
	return (0);
}
