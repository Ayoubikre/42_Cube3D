/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3drendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:28:03 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/28 00:22:15 by anktiri          ###   ########.fr       */
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
	vars->lineH = (int)(vars->proj / vars->wall_dist);
	vars->drawStart = -vars->lineH / 2 + HEIGHT / 2;
	vars->drawEnd = vars->lineH / 2 + HEIGHT / 2;
	if (vars->drawStart < 0)
		vars->drawStart = 0;
	if (vars->drawEnd >= HEIGHT)
		vars->drawEnd = HEIGHT - 1;
}

int	get_text_index(t_ray *ray)
{
	if (ray->hit == 2)
		return (DOOR);
	else if (ray->hit == 4)
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

void	ft_render_column(t_data *data, t_render_vars *vars)
{
	int		tex_index;
	int		tex_x;
	double	wall_x;

	calculate_wall_projection(data, vars);
	vars->ray_side = data->rays[vars->ray_i].side;
	tex_index = get_text_index(&data->rays[vars->ray_i]);
	wall_x = calculate_wall_x(data, vars);
	tex_x = calculate_texture_x(data, vars, wall_x, tex_index);
	draw_column_pixels(data, vars, tex_index, tex_x);
}

void	fps(void)
{
	static double	last_t = 0.0;
	static int		frames = 0;
	double			now;
	double			fps;

	now = mlx_get_time();
	if (last_t == 0.0)
		last_t = now;
	frames++;
	if (now - last_t >= 1.0)
	{
		fps = frames / (now - last_t);
		printf("FPS: %.2f\n", fps);
		frames = 0;
		last_t = now;
	}
}

void	ft_render3d(t_data *data)
{
	t_render_vars	vars;

	draw_background(data);
	vars.proj = ((double)WIDTH / 2.0) / tan(data->fov / 2.0);
	vars.column = 0;
	while (vars.column < WIDTH)
	{
		vars.ray_i = (int)((double)vars.column / (double)WIDTH * (double)RAYS);
		if (vars.ray_i < 0)
			vars.ray_i = 0;
		if (vars.ray_i >= RAYS)
			vars.ray_i = RAYS - 1;
		ft_render_column(data, &vars);
		vars.column++;
	}
	fps();
}
