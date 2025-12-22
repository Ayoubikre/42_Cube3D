/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:53:54 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 16:48:25 by aakritah         ###   ########.fr       */
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
	data->mini.height = HEIGHT / 6;
	data->mini.width = WIDTH / 6;
	data->mini.cell_size = 20;
	data->mini.p_size = 8;
	{
		data->mini.ptr_img = mlx_new_image(game->mlx.ptr, data->mini.width,
				data->mini.height);
		if (!data->mini.ptr_img)
			return (-1);
		mlx_image_to_window(game->mlx.ptr, data->mini.ptr_img, 43, 43);
	}
	ft_init_minimap_borders(game, data);
	return (0);
}

int	ft_init_mlx_bigmap(t_game *game, t_data *data)
{
	data->big.height = HEIGHT;
	data->big.width = WIDTH;
	data->big.cell_size = 40;
	data->big.p_size = 16;
	data->big.offset_x = 0;
	data->big.offset_y = 0;
	{
		data->big.ptr_img = mlx_new_image(game->mlx.ptr, data->big.width,
				data->big.height);
		if (!data->big.ptr_img)
			return (-1);
		data->big.ptr_img->enabled = false;
		mlx_image_to_window(game->mlx.ptr, data->big.ptr_img, 0, 0);
	}
	return (0);
}

void	ft_init_hand_animation(t_game *game)
{
	ft_strlcpy(game->hand.folder, "Tools/animation/zombie/zombie", 256);
	game->hand.total_frames = 56;
	game->hand.current_frame = 0;
	game->hand.frame_delay_counter = 0;
	game->hand.frame_delay = 2;
	game->hand.ptr_img = NULL;
}

int	ft_init_lvl(t_game *game, t_data *data)
{
	if (ft_init_mlx_map(game) == -1)
	{
		return (ft_destroy_lvl(game, data, 0), -1);
	}
	if (ft_init_mlx_minimap(game, data) == -1)
	{
		return (ft_destroy_lvl(game, data, 1), -1);
	}
	if (ft_init_mlx_bigmap(game, data) == -1)
	{
		return (ft_destroy_lvl(game, data, 1), -1);
	}
	if (ft_init_textures(data) == -1)
	{
		return (ft_destroy_lvl(game, data, 2), -1);
	}
	{
		ft_init_hand_animation(game);
	}
	{
		ft_draw_level_text(game);
		ft_reset_player_data(data);
	}
	return (0);
}
