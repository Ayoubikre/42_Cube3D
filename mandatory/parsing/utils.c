/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 17:00:29 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/23 04:23:44 by anktiri          ###   ########.fr       */
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

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->grid_y)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->grid_y = 0;
	map->grid_x = 0;
}

void	free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < TEX_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]);
			data->textures[i] = NULL;
		}
		i++;
	}
	free_map(&data->map);
}

void	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
