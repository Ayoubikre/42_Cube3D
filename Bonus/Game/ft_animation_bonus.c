/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:36:55 by noctis            #+#    #+#             */
/*   Updated: 2025/12/15 05:11:47 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_display_frame(t_game *game)
{
	char			*num;
	char			*path;
	mlx_texture_t	*tex;

	if (game->stage_anim.current_img)
		mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
	num = ft_itoa(game->stage_anim.current_frame + 1);
	path = ft_strjoin(game->stage_anim.folder, num);
	free(num);
	num = ft_strjoin(path, ".png");
	free(path);
	tex = mlx_load_png(num);
	free(num);
	if (!tex)
		return ;
	game->stage_anim.current_img = mlx_texture_to_image(game->mlx.ptr, tex);
	mlx_resize_image(game->stage_anim.current_img, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx.ptr, game->stage_anim.current_img, 0, 0);
	mlx_delete_texture(tex);
}

void	ft_handle_space_key(t_game *game)
{
	if (game->stage_anim.stage == 0 || game->stage_anim.stage == 1)
	{
		ft_strlcpy(game->stage_anim.folder, "Tools/animation/Loading/loading",
			256);
		game->stage_anim.total_frames = 16;
		game->stage_anim.frame_delay = 25;
		game->stage_anim.current_frame = 0;
		game->stage_anim.stage = 2;
	}
	else if (game->stage_anim.stage == 3 || game->stage_anim.stage == 4)
	{
		mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
		game->stage_anim.stage = 1;
	}
	ft_display_frame(game);
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
			if (game->stage_anim.stage == 2)
			{
				game->stage_anim.is_active = 0;
				if (game->stage_anim.current_img)
					mlx_delete_image(game->mlx.ptr,
						game->stage_anim.current_img);
				game->stage_anim.current_img = NULL;
			}
			else
				game->stage_anim.current_frame = 0;
		}
	}
}

void	ft_start_animation(t_game *game, char *folder, int frames, int stage)
{
	ft_strlcpy(game->stage_anim.folder, folder, 256);
	game->stage_anim.total_frames = frames;
	game->stage_anim.current_frame = 0;
	game->stage_anim.frame_counter = 0;
	game->stage_anim.frame_delay = 30;
	if (stage == 1)
		game->stage_anim.frame_delay = 20;
	game->stage_anim.is_active = 1;
	game->stage_anim.current_img = NULL;
	game->stage_anim.stage = stage;
	ft_display_frame(game);
}

int	ft_animation(t_game *game)
{
	ft_update_stage_animation(game);
	if (game->stage_anim.is_active)
		return (1);
	if (game->g_state == GAME_START)
	{
		return (ft_start_animation(game, "Tools/animation/start/start", 8, 0),
			game->g_state = DEFAULT, 1);
	}
	else if (game->g_state == LVL_SWITCH)
	{
		return (ft_start_animation(game, "Tools/animation/stage/stage", 8, 1),
			game->g_state = DEFAULT, 1);
	}
	else if (game->g_state == GAME_END)
	{
		return (ft_start_animation(game, "Tools/animation/ending/ending", 6, 3),
			game->g_state = DEFAULT, 1);
	}
	else if (game->g_state == PLAYER_DEAD)
	{
		return (ft_start_animation(game, "Tools/animation/failed/failed", 8, 4),
			game->g_state = DEFAULT, 1);
	}
	return (game->g_state = DEFAULT, 0);
}
