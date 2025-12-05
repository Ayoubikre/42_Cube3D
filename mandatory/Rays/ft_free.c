/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:50:35 by noctis            #+#    #+#             */
/*   Updated: 2025/12/05 02:11:21 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_free_mlx(t_game *game)
{
	if (game->mlx.ptr)
	{
		if (game->level_text_img)
			mlx_delete_image(game->mlx.ptr, game->level_text_img);
		mlx_delete_image(game->mlx.ptr, game->mlx.ptr_img);
		mlx_terminate(game->mlx.ptr);
	}
}

void	ft_free_map(t_map *map)
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

void	ft_free_data(t_data *data)
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
	if (data->next_file)
		free(data->next_file);
	if (data->rays)
		free(data->rays);
	ft_free_map(&data->map);
}

void	ft_free_lvl(t_levels *lvl)
{
	if (lvl->path)
		free(lvl->path);
	ft_free_data(&lvl->data);
	free(lvl);
}

void	ft_free_list(t_game *game)
{
	if (!game)
		return ;
	ft_free_mlx(game);
	while (game->lvls)
	{
		game->c_lvl = game->lvls;
		game->lvls = game->lvls->next;
		ft_free_lvl(game->c_lvl);
	}
	free(game->lvls);
}
