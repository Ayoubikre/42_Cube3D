/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:56:32 by akzaza            #+#    #+#             */
/*   Updated: 2025/12/03 13:54:32 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->textures[i] = NULL;
		data->load_textures[i].tex = NULL;
		data->load_textures[i].loaded = 0;
		i++;
	}
	data->floor_color = (t_color){0, 0, 0};
	data->ceiling_color = (t_color){0, 0, 0};
	data->map.grid = NULL;
	data->map.grid_x = 0;
	data->map.grid_y = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.orientation = 0;
	data->next_file = NULL;
	i = 0;
	while (i < ELEM_COUNT)
	{
		data->parsed[i] = 0;
		i++;
	}
}

int	all_elements_parsed(t_data *data)
{
	int	i;

	i = 0;
	while (i < ELEM_COUNT)
	{
		if (data->parsed[i] == 0)
			return (0);
		i++;
	}
	return (1);
}


int	main_core(t_data *data, char *file_name)
{
	init_data(data);
	// ft_memset(data, 0, sizeof(t_data));
	if (!check_file(file_name, 1))
	{
		print_error("Invalid file extension (must be .cub)");
		return (1);
	}
	if (!parse_file(file_name, data))
	{
		free_data(data);
		return (1);
	}
	print_parse_results(data);
	return (0);
}
