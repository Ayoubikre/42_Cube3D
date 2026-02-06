/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:02:11 by aakritah          #+#    #+#             */
/*   Updated: 2025/12/22 18:04:34 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_update_stage_animation_2(t_game *game)
{
	if (game->stage_anim.stage == 2)
	{
		game->stage_anim.is_active = 0;
		if (game->stage_anim.current_img)
			mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
		game->stage_anim.current_img = NULL;
	}
	else if (game->stage_anim.stage == 5)
	{
		game->stage_anim.is_active = 0;
		if (game->stage_anim.current_img)
			mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
		game->stage_anim.current_img = NULL;
		game->stage_anim.timer = 0;
		game->g_state = GAME_END;
		return ;
	}
	else
		game->stage_anim.current_frame = 0;
}

void	ft_update_stage_animation(t_game *game)
{
	if (!game->stage_anim.is_active)
		return ;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_SPACE))
	{
		ft_handle_space_key(game);
		return ;
	}
	if (++game->stage_anim.frame_counter >= game->stage_anim.frame_delay)
	{
		game->stage_anim.frame_counter = 0;
		ft_display_frame(game);
		if (++game->stage_anim.current_frame >= game->stage_anim.total_frames)
		{
			ft_update_stage_animation_2(game);
		}
	}
}
