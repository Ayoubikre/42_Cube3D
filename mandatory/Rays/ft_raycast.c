/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 02:15:23 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_init_ray_data(t_data *data, t_ray *ray, int i, double r)
{
	ray->angle = (data->ang - (data->fov / 2)) + (i * r);
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	else if (ray->angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
	ray->ang_cos = cos(ray->angle);
	ray->const_x = fabs(data->map.cell_s / ray->ang_cos);
	ray->x = floor(data->player.pos_x);
	ray->ang_sin = sin(ray->angle);
	ray->const_y = fabs(data->map.cell_s / ray->ang_sin);
	ray->y = floor(data->player.pos_y);
	ray->hit = 0;
}

void	ft_first_cell_len(t_data *data, t_ray *ray)
{
	if (ray->ang_cos < 0)
	{
		ray->step_x = -1;
		ray->extra_x = (data->player.pos_x - ray->x) * ray->const_x;
	}
	else
	{
		ray->step_x = 1;
		ray->extra_x = (ray->x + 1.0 - data->player.pos_x) * ray->const_x;
	}
	if (ray->ang_sin < 0)
	{
		ray->step_y = -1;
		ray->extra_y = (data->player.pos_y - ray->y) * ray->const_y;
	}
	else
	{
		ray->step_y = 1;
		ray->extra_y = (ray->y + 1.0 - data->player.pos_y) * ray->const_y;
	}
}

void	ft_set_info(t_ray *ray, char w)
{
	if (w == '1' || w == '2' || w == '4')
	{
		if (w == '2')
			ray->hit = 2;
		else if (w == '4')
			ray->hit = 4;
		else
			ray->hit = 1;
	}
	if (ray->side == 0)
	{
		if (ray->ang_cos < 0)
			ray->drc = 'E';
		else
			ray->drc = 'W';
	}
	else
	{
		if (ray->ang_sin < 0)
			ray->drc = 'S';
		else
			ray->drc = 'N';
	}
}

void	ft_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->extra_x < ray->extra_y)
		{
			ray->extra_x += ray->const_x;
			ray->x += ray->step_x;
			ray->side = 0;
			ray->len = (ray->x - data->player.pos_x + (1 - ray->step_x) / 2)
				/ ray->ang_cos;
		}
		else
		{
			ray->extra_y += ray->const_y;
			ray->y += ray->step_y;
			ray->side = 1;
			ray->len = (ray->y - data->player.pos_y + (1 - ray->step_y) / 2)
				/ ray->ang_sin;
		}
		ft_set_info(ray, data->map.grid[ray->y][ray->x]);
	}
}

void	ft_raycasting(t_game *game, t_data *data)
{
	int		i;
	double	r;

	i = -1;
	r = data->fov / RAYS;
	while (++i < RAYS)
	{
		ft_init_ray_data(data, &data->rays[i], i, r);
		ft_first_cell_len(data, &data->rays[i]);
		ft_dda(data, &data->rays[i]);
		ft_draw_ray(game, data, data->rays[i].angle, data->rays[i].len);
	}
}
