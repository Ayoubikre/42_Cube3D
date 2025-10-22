/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/22 23:04:37 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return ((print_error("Usage: ./cub3D <map.cub>")), 1);
	if (main_core(&data, av[1]))
		return (1);






	free_data(&data);
	return (0);
}
