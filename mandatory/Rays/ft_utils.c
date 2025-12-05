/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:55:43 by noctis            #+#    #+#             */
/*   Updated: 2025/12/05 02:42:48 by noctis           ###   ########.fr       */
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

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*t;

	int (s), (i), (j), (k);
	if (!s1 || !s2 || !s3)
		return (NULL);
	s = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	t = malloc(s + 1);
	if (!t)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		t[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		t[i++] = s2[j++];
	k = 0;
	while (s3[k] != '\0')
		t[i++] = s3[k++];
	t[i] = '\0';
	return (t);
}
