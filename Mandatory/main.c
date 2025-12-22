/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/22 19:56:49 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	t(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;

	atexit(t);
	if (ac != 2)
		return ((print_error("Usage: ./cub3D <map.cub>")), 1);
	if (ft_wrap_main_core(&game, av[1]))
		ft_wrap_start_game(&game);
	return (ft_free_list(&game), 0);
}
