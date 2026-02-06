/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 13:10:59 by aakritah          #+#    #+#             */
/*   Updated: 2025/12/22 17:08:58 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_display_frame_2(t_game *game)
{
	char			*num;
	char			*path;
	mlx_texture_t	*tex;

	if (game->hand.ptr_img)
		mlx_delete_image(game->mlx.ptr, game->hand.ptr_img);
	num = ft_itoa(game->hand.current_frame);
	path = ft_strjoin3(game->hand.folder, num, ".png");
	free(num);
	tex = mlx_load_png(path);
	free(path);
	if (!tex)
		return ;
	game->hand.ptr_img = mlx_texture_to_image(game->mlx.ptr, tex);
	mlx_delete_texture(tex);
	mlx_image_to_window(game->mlx.ptr, game->hand.ptr_img, 0, HEIGHT
		- game->hand.ptr_img->height);
}

void	ft_hands(t_game *game)
{
	if (++game->hand.frame_delay_counter < game->hand.frame_delay)
		return ;
	game->hand.frame_delay_counter = 0;
	game->hand.current_frame++;
	if (game->hand.current_frame >= game->hand.total_frames)
		game->hand.current_frame = 0;
	ft_display_frame_2(game);
}
