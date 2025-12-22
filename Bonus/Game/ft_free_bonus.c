/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:50:35 by noctis            #+#    #+#             */
/*   Updated: 2025/12/22 16:20:05 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_free_mlx(t_game *game)
{
	if (!game || !game->mlx.ptr)
		return ;
	if (game->level_text_img)
	{
		mlx_delete_image(game->mlx.ptr, game->level_text_img);
		game->level_text_img = NULL;
	}
	if (game->stage_anim.current_img)
	{
		mlx_delete_image(game->mlx.ptr, game->stage_anim.current_img);
		game->stage_anim.current_img = NULL;
	}
	if (game->hand.ptr_img)
	{
		mlx_delete_image(game->mlx.ptr, game->hand.ptr_img);
		game->hand.ptr_img = NULL;
	}
	if (game->mlx.ptr_img)
	{
		mlx_delete_image(game->mlx.ptr, game->mlx.ptr_img);
		game->mlx.ptr_img = NULL;
	}
	mlx_terminate(game->mlx.ptr);
	game->mlx.ptr = NULL;
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

void	ft_free_data(t_game *game, t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	while (++i < TEX_COUNT)
	{
		if (data->textures[i])
		{
			free(data->textures[i]);
			data->textures[i] = NULL;
		}
	}
	cleanup_textures(data);
	if (data->next_file)
		free(data->next_file);
	if (data->rays)
		free(data->rays);
	if (data->big.ptr_img)
		mlx_delete_image(game->mlx.ptr, data->big.ptr_img);
	if (data->mini.ptr_img)
		mlx_delete_image(game->mlx.ptr, data->mini.ptr_img);
	if (data->mini.cadre_img)
		mlx_delete_image(game->mlx.ptr, data->mini.cadre_img);
	ft_free_map(&data->map);
}

void	ft_free_lvl(t_game *game, t_levels *lvl)
{
	if (lvl->path)
		free(lvl->path);
	ft_free_data(game, &lvl->data);
	free(lvl);
}

void	ft_free_list(t_game *game)
{
	if (!game)
		return ;
	while (game->lvls)
	{
		game->c_lvl = game->lvls;
		game->lvls = game->lvls->next;
		ft_free_lvl(game, game->c_lvl);
	}
	ft_free_mlx(game);
}
