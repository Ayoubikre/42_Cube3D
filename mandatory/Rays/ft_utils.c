/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:55:43 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 01:40:38 by noctis           ###   ########.fr       */
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
