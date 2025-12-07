/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 04:39:32 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/05 02:40:15 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	norm_pi(double a)
{
	if (a > M_PI)
		a -= 2.0 * M_PI;
	else if (a < -M_PI)
		a += 2.0 * M_PI;
	return (a);
}

double	calculate_wall_x(t_data *data, t_render_vars *vars)
{
	t_ray	*ray;
	double	wall_x;

	ray = &data->rays[vars->ray_i];
	if (ray->side == 0)
		wall_x = data->player.pos_y + ray->len * ray->ang_sin;
	else
		wall_x = data->player.pos_x + ray->len * ray->ang_cos;
	wall_x -= floor(wall_x);
	return (wall_x);
}

uint32_t	get_fallback_color(int tex_index)
{
	if (tex_index == NORTH)
		return (0xFF0000FF);
	else if (tex_index == SOUTH)
		return (0x00FF00FF);
	else if (tex_index == WEST)
		return (0x0000FFFF);
	else if (tex_index == EAST)
		return (0xFFFF00FF);
	return (0xFFFFFFFF);
}

uint32_t	get_texture_pixel(t_data *data, int tex_index, int x, int y)
{
	mlx_texture_t	*tex;
	int				index;
	uint8_t			*pixels;

	if (data->load_textures[tex_index].loaded
		&& data->load_textures[tex_index].tex)
	{
		tex = data->load_textures[tex_index].tex;
		if (x < 0 || x >= (int)tex->width || y < 0 || y >= (int)tex->height)
			return (get_fallback_color(tex_index));
		index = (y * tex->width + x) * tex->bytes_per_pixel;
		pixels = tex->pixels;
		return ((pixels[index] << 24) | (pixels[index
					+ 1] << 16) | (pixels[index + 2] << 8) | pixels[index + 3]);
	}
	return (get_fallback_color(tex_index));
}

uint32_t	apply_fog(uint32_t color, double distance)
{
	double		fog_factor;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;

	if (distance >= VISIBLE_DISTANCE)
		return (0x000000FF);
	fog_factor = distance / VISIBLE_DISTANCE;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (uint8_t)(r * (1.0 - fog_factor));
	g = (uint8_t)(g * (1.0 - fog_factor));
	b = (uint8_t)(b * (1.0 - fog_factor));
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	draw_column_pixels(t_game *game, t_render_vars *vars, int tex_index,
		int tex_x)
{
	int			y;
	int			d;
	int			tex_y;
	int			tex_height;
	uint32_t	color;

	tex_height = game->c_lvl->data.load_textures[tex_index].tex->height;
	if (vars->line_h <= 0 || tex_height <= 0)
		return ;
	y = vars->draw_start;
	while (y <= vars->draw_end)
	{
		d = y * 256 - HEIGHT * 128 + vars->line_h * 128;
		tex_y = ((d * tex_height) / vars->line_h) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_height)
			tex_y = tex_height - 1;
		color = get_texture_pixel(&game->c_lvl->data, tex_index, tex_x, tex_y);
		color = apply_fog(color, vars->wall_dist);
		put_px(game->mlx.ptr_img, vars->column, y, color);
		y++;
	}
}
