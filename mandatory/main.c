/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/24 19:34:11 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

// void t()
// {
// 	system("leaks -q cub3D");
// }

int	main(int ac, char **av)
{
	// atexit(t);
	t_data	data;

	if (ac != 2)
		return ((print_error("Usage: ./cub3D <map.cub>")), 1);
	if (main_core(&data, av[1]))
		return (1);
	if (ft_start(&data)==-1)
		return 1;






	return (free_data(&data), 0);
}
