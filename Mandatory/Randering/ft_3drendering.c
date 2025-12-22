/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3drendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:28:03 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/22 19:42:07 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_projection(t_data *data, t_render_vars *vars)
{
	t_ray	*ray;

	ray = &data->rays[vars->ray_i];
	vars->wall_dist = ray->len * cos(ray->angle - data->ang);
	if (vars->wall_dist < 1e-6)
		vars->wall_dist = 1e-6;
	vars->line_h = (int)(vars->proj / vars->wall_dist);
	vars->draw_start = -vars->line_h / 2 + HEIGHT / 2;
	vars->draw_end = vars->line_h / 2 + HEIGHT / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	if (vars->draw_end >= HEIGHT)
		vars->draw_end = HEIGHT - 1;
}

int	get_text_index(t_ray *ray)
{
	if (ray->hit == 2)
		return (DOOR);
	else if (ray->hit == 4 || ray->hit == 5)
		return (PORTAL);
	else if (ray->drc == 'N')
		return (NORTH);
	else if (ray->drc == 'S')
		return (SOUTH);
	else if (ray->drc == 'W')
		return (WEST);
	else if (ray->drc == 'E')
		return (EAST);
	return (-1);
}

void	ft_render_column(t_game *game, t_data *data, t_render_vars *vars)
{
	int		tex_index;
	int		tex_x;
	double	wall_x;

	calculate_wall_projection(data, vars);
	vars->ray_side = data->rays[vars->ray_i].side;
	tex_index = get_text_index(&data->rays[vars->ray_i]);
	wall_x = calculate_wall_x(data, vars);
	tex_x = calculate_texture_x(data, vars, wall_x, tex_index);
	draw_column_pixels(game, vars, tex_index, tex_x);
}

void	ft_render3d(t_game *game, t_data *data)
{
	t_render_vars	vars;

	draw_background(game, data);
	vars.proj = ((double)WIDTH / 2.0) / tan(data->fov / 2.0);
	vars.column = 0;
	while (vars.column < WIDTH)
	{
		vars.ray_i = (int)((double)vars.column / (double)WIDTH * (double)RAYS);
		if (vars.ray_i < 0)
			vars.ray_i = 0;
		if (vars.ray_i >= RAYS)
			vars.ray_i = RAYS - 1;
		ft_render_column(game, data, &vars);
		vars.column++;
	}
}
