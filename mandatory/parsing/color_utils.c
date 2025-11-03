/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:02:34 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/12 22:25:42 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = (i++, -1);
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i++] - '0');
		if (result > 255)
			return (-1);
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (sign == -1 || str[i] != '\0')
		return (-1);
	return ((int)result);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	free_message(char **str, int flag)
{
	if (flag == 1)
	{
		free_split(str);
		print_error("Color must have exactly 3 RGB values");
	}
	else if (flag == 2)
	{
		free_split(str);
		print_error("Invalid R value (must be 0-255)");
	}
	else if (flag == 3)
	{
		free_split(str);
		print_error("Invalid G value (must be 0-255)");
	}
	else if (flag == 4)
	{
		free_split(str);
		print_error("Invalid B value (must be 0-255)");
	}
	return (0);
}

int	parse_rgb(char *str, t_color *color)
{
	char	**rgb_split;
	int		count;

	if (!str || !color)
		return (0);
	rgb_split = ft_split(str, ',');
	if (!rgb_split)
		return (0);
	count = 0;
	while (rgb_split[count])
		count++;
	if (count != 3)
		return (free_message(rgb_split, 1));
	color->r = get_color(rgb_split[0]);
	if (color->r == -1)
		return (free_message(rgb_split, 2));
	color->g = get_color(rgb_split[1]);
	if (color->g == -1)
		return (free_message(rgb_split, 3));
	color->b = get_color(rgb_split[2]);
	if (color->b == -1)
		return (free_message(rgb_split, 4));
	free_split(rgb_split);
	return (1);
}
