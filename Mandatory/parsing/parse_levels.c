/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_levels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 21:18:20 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/03 18:52:37 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_lvl_line(char *line)
{
	char	*str;

	if (!line)
		return (0);
	str = skip_spaces(line);
	if (!str || !*str)
		return (0);
	if (ft_strncmp(str, "LV", 2) == 0 && (str[2] == '\0' || ft_isspace(str[2])))
		return (1);
	return (0);
}

int	parse_lvl_line(char *line, t_data *data)
{
	parse_texture_line(line, data, 1);
	if (!check_file(data->next_file, 3))
	{
		print_error("LV file does not exist or is not readable");
		return (0);
	}
	return (1);
}
