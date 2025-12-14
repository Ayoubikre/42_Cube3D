/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:36:55 by noctis            #+#    #+#             */
/*   Updated: 2025/12/13 13:22:35 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	display_frame(t_game *game)
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

static void	handle_space_key(t_game *game)
{
	if (game->stage_anim.stage == 0)
	{
		game->stage_anim.is_active = 0;
		if (game->stage_anim.current_img)
			mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
		game->stage_anim.current_img = NULL;
	}
	else if (game->stage_anim.stage == 1)
	{
		ft_strlcpy(game->stage_anim.folder,
			"Tools/animation/Loading_animation/loading_screen", 256);
		game->stage_anim.total_frames = 8;
		game->stage_anim.frame_delay = 20;
		game->stage_anim.current_frame = 0;
		game->stage_anim.stage = 2;
	}
	else if (game->stage_anim.stage == 3)
		mlx_close_window(game->mlx.ptr);
}

void	update_stage_animation(t_game *game)
{
	if (!game->stage_anim.is_active)
		return ;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_SPACE))
	{
		handle_space_key(game);
		return ;
	}
	if (++game->stage_anim.frame_counter >= game->stage_anim.frame_delay)
	{
		game->stage_anim.frame_counter = 0;
		display_frame(game);
		if (++game->stage_anim.current_frame >= game->stage_anim.total_frames)
		{
			if (game->stage_anim.stage == 0 || game->stage_anim.stage == 2)
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

void	start_animation(t_game *game, char *folder, int frames, int delay,
		int stage)
{
	ft_strlcpy(game->stage_anim.folder, folder, 256);
	game->stage_anim.total_frames = frames;
	game->stage_anim.current_frame = 0;
	game->stage_anim.frame_counter = 0;
	game->stage_anim.frame_delay = delay;
	game->stage_anim.is_active = 1;
	game->stage_anim.current_img = NULL;
	game->stage_anim.stage = stage;
}

void	ft_start_animation(t_game *game, t_data *data)
{
	(void)data;
	start_animation(game,
		"Tools/animation/Loading_animation/loading_screen", 8, 20, 0);
}

void	ft_switch_animation(t_game *game, t_data *data)
{
	(void)data;
	start_animation(game, "Tools/animation/stage_complete/stage_complete", 8,
		20, 1);
}

void	ft_dead_animation(t_game *game, t_data *data)
{
	(void)game;
	(void)data;
	// Dead player animation has been disabled as requested
}

void	ft_end_animation(t_game *game, t_data *data)
{
	(void)data;
	start_animation(game,
		"Tools/animation/complete_animation/complete_animation", 6, 30, 3);
}