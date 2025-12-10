/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:52:15 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 19:45:34 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_speed(t_game *game, t_data *data)
{
	double	fov_max;
	double	sprint_speed;
	double	target_fov;
	double	target_speed;

	fov_max = ft_rad(120);
	sprint_speed = 0.50;
	target_fov = ft_rad(60);
	target_speed = 0.10;
	if (mlx_is_key_down(game->mlx.ptr, MLX_KEY_LEFT_SHIFT))
	{
		target_fov = fov_max;
		target_speed = sprint_speed;
	}
	data->fov += (target_fov - data->fov) * 0.05;
	if (data->fov > fov_max)
		data->fov = fov_max;
	data->move_speed += (target_speed - data->move_speed) * 0.05;
	if (data->move_speed > sprint_speed)
		data->move_speed = sprint_speed;
}

void	ft_update_mouse_angle(double xpos, double ypos, void *param)
{
	t_game	*game;
	t_data	*data;
	double	new_x;

	(void)ypos;
	game = (t_game *)param;
	data = &game->c_lvl->data;
	if (data->player.mouse_l_p == -1)
	{
		data->player.mouse_l_p = xpos;
		return ;
	}
	new_x = xpos - data->player.mouse_l_p;
	data->player.mouse_l_p = xpos;
	data->ang += new_x * MOUSE_SP;
	if (data->ang < 0)
		data->ang += 2 * M_PI;
	else if (data->ang >= 2 * M_PI)
		data->ang -= 2 * M_PI;
}
