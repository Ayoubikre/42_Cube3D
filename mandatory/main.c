/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/03 14:22:52 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	t(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	// atexit(t);
	if (ac != 2)
		return ((print_error("Usage: ./cub3D <map.cub>")), 1);
	if (main_core(&data, av[1]))
		return (1);
	// if (ft_start(&data) == -1)
	// 	return (1);
	return (free_data(&data), 0);
}


// t_game
// │
// ├── mlx_t *mlx     ← only one MLX instance & window
// │
// └── t_level *levels  ← linked list
//        │
//        ├── char *path
//        ├── t_data *data   ← parsed map + textures + player spawn
//        └── next / prev
