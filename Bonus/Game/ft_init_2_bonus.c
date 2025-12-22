/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 04:30:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 20:22:22 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_init_minimap_borders(t_game *game, t_data *data)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./Tools/textures/extra/Cadre_map.png");
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
