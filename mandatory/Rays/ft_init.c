/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:53:54 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 03:15:24 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_mlx_map(t_game *game)
{
	game->mlx.ptr_img = mlx_new_image(game->mlx.ptr, WIDTH, HEIGHT);
	if (!game->mlx.ptr_img)
		return (-1);
	game->mlx.id_img = mlx_image_to_window(game->mlx.ptr, game->mlx.ptr_img, 0,
			0);
	if (game->mlx.id_img == -1)
		return (-1);
	return (0);
}

int	ft_init_mlx_minimap(t_game *game, t_data *data)
{
	data->mini.ptr_img = mlx_new_image(game->mlx.ptr, WIDTH / 5, HEIGHT / 3);
	if (!data->mini.ptr_img)
		return (-1);
	data->mini.id_img = mlx_image_to_window(game->mlx.ptr, data->mini.ptr_img,
			10, 10);
	if (data->mini.id_img == -1)
		return (-1);
	return (0);
}

void	ft_destroy_lvl(t_game *game, t_data *data, int f)
{
	if (f >= 0)
	{
		if (game->mlx.ptr_img)
			mlx_delete_image(game->mlx.ptr, game->mlx.ptr_img);
	}
	if (f >= 1)
	{
		if (data->mini.ptr_img)
			mlx_delete_image(game->mlx.ptr, data->mini.ptr_img);
	}
	if (f >= 2)
	{
		cleanup_textures(data);
	}
}

void	ft_reset_player_data(t_data *data)
{
	data->player.mouse_l_p = data->player_bak.mouse_l_p;
	data->player.orientation = data->player_bak.orientation;
	data->player.pos_x = data->player_bak.pos_x;
	data->player.pos_y = data->player_bak.pos_y;
	data->ang = data->player_bak.ang;
}

int	ft_init_lvl(t_game *game, t_data *data)
{
	ft_reset_player_data(data);
	if (ft_init_mlx_map(game) == -1)
		return (ft_destroy_lvl(game, data, 0), -1);
	// if ( ft_init_mlx_minimap(game, data) == -1)
	// 	return (ft_destroy_lvl(game , data, 1), -1);
	if (ft_init_textures(data) == -1)
		return (ft_destroy_lvl(game, data, 2), -1);
	return (0);
}
