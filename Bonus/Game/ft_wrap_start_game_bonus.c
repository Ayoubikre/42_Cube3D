/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap_start_game_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:52:53 by noctis            #+#    #+#             */
/*   Updated: 2025/12/15 03:16:21 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_all(void *param)
{
	t_game	*game;
	t_data	*data;

	game = (t_game *)param;
	data = &game->c_lvl->data;
	if (ft_animation(game))
		return ;
	ft_capture_player_moves(game, data);
	ft_speed(game, data);
	ft_raycasting(data);
	ft_open_and_close_doors(data, 1);
	ft_draw_level_text(game);
	ft_minimap(data);
	ft_render3d(game, data);
}

void	ft_hooks(t_game *game)
{
	mlx_key_hook(game->mlx.ptr, ft_capture_keys, (void *)game);
	mlx_cursor_hook(game->mlx.ptr, ft_update_mouse_angle, (void *)game);
	mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_DISABLED);
}

void	ft_start_game(t_game *game)
{
	ft_hooks(game);
	mlx_loop_hook(game->mlx.ptr, ft_all, (void *)game);
	mlx_loop(game->mlx.ptr);
}

int	ft_wrap_start_game(t_game *game)
{
	game->c_lvl = game->lvls;
	game->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!game->mlx.ptr)
		return (0);
	if (ft_init_lvl(game, &game->c_lvl->data) == -1)
		return (0);
	ft_start_game(game);
	return (1);
}
