/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lvls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:01:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 19:52:20 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_switch_lvl(t_game *game, t_data *data)
{
	if (data->rays[RAYS / 2].len <= 2.0 && data->rays[RAYS / 2].hit == 4)
	{
		ft_destroy_lvl(game, data, 3);
		if (game->c_lvl->next)
		{
			game->c_lvl = game->c_lvl->next;
			game->g_state = LVL_SWITCH;
		}
		else
		{
			game->c_lvl = game->lvls;
			game->g_state = GAME_END;
		}
		ft_init_lvl(game, &game->c_lvl->data);
	}
}

void	ft_draw_level_text(t_game *game)
{
	char	*lvl_str;
	char	*curr;
	char	*total;
	char	*final_str;
	int		x;

	if (!game || !game->c_lvl)
		return ;
	if (game->level_text_img)
	{
		mlx_delete_image(game->mlx.ptr, game->level_text_img);
		game->level_text_img = NULL;
	}
	curr = ft_itoa(game->c_lvl->id);
	total = ft_itoa(game->id_max);
	if (!curr || !total)
		return ;
	lvl_str = ft_strjoin3("Lvl ", curr, " / ");
	final_str = ft_strjoin3(lvl_str, total, "");
	x = WIDTH - (ft_strlen(final_str) * 10) - 10;
	game->level_text_img = mlx_put_string(game->mlx.ptr, final_str, x, 10);
	free(curr);
	free(total);
	free(lvl_str);
	free(final_str);
}
