/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:55:43 by noctis            #+#    #+#             */
/*   Updated: 2025/11/29 21:00:03 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	ft_color(t_color clr)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)(clr.r & 0xFF);
	g = (unsigned int)(clr.g & 0xFF);
	b = (unsigned int)(clr.b & 0xFF);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFFu);
}

double	ft_rad(double x)
{
	return (x * M_PI / 180.0);
}

double	ft_deg(double x)
{
	return (x * 180.0 / M_PI);
}

void	ft_clean(t_data *data, int f)
{
	if (f >= 0)
		mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
	if (f >= 1)
		mlx_delete_image(data->mlx.ptr, data->mini.ptr_img);
	if (f >= 2)
		free(data->rays);
	if (f >= 3)
	{
		cleanup_textures(data);
		mlx_delete_image(data->mlx.ptr, data->mini.ptr_img);
	}
	mlx_terminate(data->mlx.ptr);
}
