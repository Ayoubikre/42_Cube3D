/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:52:53 by noctis            #+#    #+#             */
/*   Updated: 2025/12/03 13:37:16 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	ft_all(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	// ft_draw_background(data, 0, 0);
	// ft_draw_map_2d(data, 0, 0);
	ft_capture_player_moves(data);
	ft_speed(data);
	// ft_draw_player_2d(data, 0, 0);
	ft_raycasting(data);
	ft_close_doors(data);
	ft_render3d(data);
}

void	ft_hooks(t_data *data)
{
	mlx_key_hook(data->mlx.ptr, ft_capture_keys, (void *)data);
	mlx_cursor_hook(data->mlx.ptr, ft_update_mouse_angle, (void *)data);
	mlx_set_cursor_mode(data->mlx.ptr, MLX_MOUSE_DISABLED);
}

int	ft_start(t_data *data)
{
	if (ft_init_game(data) == -1)
		return (-1);
	ft_hooks(data);
	mlx_loop_hook(data->mlx.ptr, ft_all, (void *)data);
	mlx_loop(data->mlx.ptr);
	return (ft_clean(data, 4), 0);
}
