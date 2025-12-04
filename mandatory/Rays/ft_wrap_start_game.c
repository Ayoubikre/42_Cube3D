/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap_start_game.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:52:53 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 03:21:56 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_all(void *param)
{
	t_game	*game;
	t_data	*data;

	game = (t_game *)param;
	data = &game->c_lvl->data;
	// ft_draw_map_2d(game,data, 0, 0);
	ft_capture_player_moves(game, data);
	ft_speed(game, data);
	// ft_draw_player_2d(data, 0, 0);
	ft_raycasting(game, data);
	ft_close_doors(data);
	ft_render3d(game, data);
}

void	ft_hooks(t_game *game, t_data *data)
{
	mlx_key_hook(game->mlx.ptr, ft_capture_keys, (void *)game);
	mlx_cursor_hook(game->mlx.ptr, ft_update_mouse_angle, (void *)data);
	mlx_set_cursor_mode(game->mlx.ptr, MLX_MOUSE_DISABLED);
}

void	ft_start_game(t_game *game, t_data *data)
{
	ft_hooks(game, data);
	mlx_loop_hook(game->mlx.ptr, ft_all, (void *)game);
	mlx_loop(game->mlx.ptr);
}

int	ft_wrap_start_game(t_game *game)
{
	game->c_lvl = game->lvls;
	game->mlx.ptr = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!game->mlx.ptr)
		return (-1);
	if (ft_init_lvl(game, &game->c_lvl->data) == -1)
		return (-1);
	ft_start_game(game, &game->c_lvl->data);
	return (0);
}
