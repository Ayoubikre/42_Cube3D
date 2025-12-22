/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 04:30:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 04:31:03 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_reset_player_data(t_data *data)
{
	data->player.mouse_l_p = -1;
	data->player.orientation = data->player_bak.orientation;
	data->player.pos_x = data->player_bak.pos_x;
	data->player.pos_y = data->player_bak.pos_y;
	data->ang = data->player_bak.ang;
}

void	ft_init_minimap_borders(t_game *game, t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./Tools/textures_2/Cadre_map.png");
	if (!texture)
		return ;
	data->mini.cadre_img = mlx_texture_to_image(game->mlx.ptr, texture);
	mlx_delete_texture(texture);
	if (data->mini.cadre_img)
	{
		mlx_resize_image(data->mini.cadre_img, data->mini.width + 65,
			data->mini.height + 65);
		mlx_image_to_window(game->mlx.ptr, data->mini.cadre_img, 0, 0);
	}
}
