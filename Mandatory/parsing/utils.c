/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:00:29 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/03 17:51:33 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *str, int flag)
{
	if (flag == 1)
	{
		if (ft_strncmp(str, ".cub", 4) == 0)
			return (1);
		return (0);
	}
	if (flag == 2)
	{
		if (ft_strncmp(str, ".xpm", 4) == 0)
			return (1);
		if (ft_strncmp(str, ".png", 4) == 0)
			return (2);
		return (0);
	}
	return (-1);
}

int	check_file(char *filename, int flag)
{
	char	*dot;
	int		fd;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	if (flag == 1 || flag == 2)
		return (check_extension(dot, flag));
	if (flag == 3)
	{
		fd = open(filename, O_RDONLY);
		close(fd);
		if (fd < 0)
			return (0);
	}
	return (-2);
}

int	all_elements_parsed(t_data *data)
{
	int	i;

	i = 0;
	while (i < ELEM_COUNT)
	{
		if (data->parsed[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
