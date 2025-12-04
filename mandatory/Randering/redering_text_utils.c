/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redering_text_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:02:25 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/04 03:22:29 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calculate_texture_x(t_data *data, t_render_vars *vars, double wallX,
		int tex_index)
{
	t_ray	*ray;
	int		tex_x;
	int		tex_width;

	ray = &data->rays[vars->ray_i];
	tex_width = data->load_textures[tex_index].tex->width;
	tex_x = (int)(wallX * tex_width);
	if (ray->side == 0)
	{
		if (ray->ang_cos < 0)
			tex_x = tex_width - tex_x - 1;
	}
	else
	{
		if (ray->ang_sin > 0)
			tex_x = tex_width - tex_x - 1;
	}
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	return (tex_x);
}

void	put_px(mlx_image_t *img, int x, int y, uint32_t color)
{
	if ((unsigned)x >= img->width || (unsigned)y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	draw_background(t_game *game, t_data *data)
{
	uint32_t	ceil_c;
	uint32_t	floor_c;
	int			y;
	int			x;
	uint32_t	color;

	ceil_c = ft_color(data->ceiling_color);
	floor_c = ft_color(data->floor_color);
	y = 0;
	while (y < HEIGHT)
	{
		color = ceil_c;
		if (y >= (HEIGHT / 2))
			color = floor_c;
		x = 0;
		while (x < WIDTH)
			put_px(game->mlx.ptr_img, x++, y, color);
		y++;
	}
}
