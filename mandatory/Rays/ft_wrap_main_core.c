/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap_main_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:56:32 by akzaza            #+#    #+#             */
/*   Updated: 2025/12/04 03:17:00 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_set_player_data_bak(t_data *data)
{
	data->player_bak.mouse_l_p = data->player.mouse_l_p;
	data->player_bak.orientation = data->player.orientation;
	data->player_bak.pos_x = data->player.pos_x;
	data->player_bak.pos_y = data->player.pos_y;
	data->player_bak.ang = data->ang;
}

int	ft_insert_dome_data(t_data *data)
{
	data->map.cell_s = (int)fmin(HEIGHT / data->map.grid_y, WIDTH
			/ data->map.grid_x);
	data->fov = ft_rad(60);
	data->move_speed = 0.10;
	data->player.mouse_l_p = -1;
	data->rays = malloc(sizeof(t_ray) * RAYS);
	if (!data->rays)
		return (-1);
	ft_memset(data->rays, 0, sizeof(t_ray) * RAYS);
	ft_set_player_data_bak(data);
	return (0);
}

int	ft_main_core(t_data *data, char *file_name)
{
	ft_memset(data, 0, sizeof(t_data));
	if (!check_file(file_name, 1))
	{
		print_error("Invalid file extension (must be .cub)");
		return (1);
	}
	if (!parse_file(file_name, data))
	{
		return (1);
	}
	if (ft_insert_dome_data(data) == -1)
		return (1);
	print_parse_results(data);
	return (0);
}

int	ft_wrap_main_core(t_game *game, char *path)
{
	int			i;
	t_levels	*tmp;

	i = 1;
	ft_memset(game, 0, sizeof(t_game));
	while (path)
	{
		tmp = ft_creat_new_list(path);
		if (!tmp)
			return (-1);
		if (ft_main_core(&tmp->data, tmp->path))
			return (ft_free_lvl(tmp), -1);
		tmp->id = i++;
		ft_add_list_end(&game->lvls, tmp);
		if (!tmp->data.next_file)
			break ;
		path = tmp->data.next_file;
	}
	game->c_lvl = game->lvls;
	game->id_max = ft_list_count(game->c_lvl);
	return (1);
}
