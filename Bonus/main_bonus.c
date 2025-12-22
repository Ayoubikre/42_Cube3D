/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/22 04:41:25 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d_bonus.h"

void	fps(void)
{
	static double	last_t = 0.0;
	static int		frames = 0;
	double			now;
	double			fps;

	now = mlx_get_time();
	if (last_t == 0.0)
		last_t = now;
	frames++;
	if (now - last_t >= 1.0)
	{
		fps = frames / (now - last_t);
		printf("FPS: %.2f\n", fps);
		frames = 0;
		last_t = now;
	}
}

void	t(void)
{
	system("leaks -q cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_game	game;

	atexit(t);
	if (ac != 2)
		return ((print_error("Usage: ./cub3D_bonus <map.cub>")), 1);
	if (ft_wrap_main_core(&game, av[1]))
		ft_wrap_start_game(&game);
	return (ft_free_list(&game), 0);
}
