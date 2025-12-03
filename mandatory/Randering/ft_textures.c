/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:40:14 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/27 15:55:33 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_xpm(t_data *data, int tex_index)
{
	xpm_t	*xpm;

	if (!data || !data->textures[tex_index])
		return (1);
	xpm = mlx_load_xpm42(data->textures[tex_index]);
	if (!xpm)
		return (1);
	data->load_textures[tex_index].tex = &xpm->texture;
	data->load_textures[tex_index].width = xpm->texture.width;
	printf("XPM text width: %d\n", data->load_textures[tex_index].width);
	data->load_textures[tex_index].height = xpm->texture.height;
	data->load_textures[tex_index].pixels = xpm->texture.pixels;
	data->load_textures[tex_index].bytes_per_pixel = \
	xpm->texture.bytes_per_pixel;
	data->load_textures[tex_index].loaded = 1;
	data->load_textures[tex_index].xpm = xpm;
	return (0);
}

int	load_png(t_data *data, int tex_index)
{
	mlx_texture_t	*texture;

	if (!data || !data->textures[tex_index])
		return (1);
	texture = mlx_load_png(data->textures[tex_index]);
	if (!texture)
		return (1);
	data->load_textures[tex_index].tex = texture;
	data->load_textures[tex_index].width = texture->width;
	data->load_textures[tex_index].height = texture->height;
	data->load_textures[tex_index].pixels = texture->pixels;
	data->load_textures[tex_index].bytes_per_pixel = texture->bytes_per_pixel;
	data->load_textures[tex_index].loaded = 1;
	data->load_textures[tex_index].xpm = NULL;
	return (0);
}

int	ft_init_textures(t_data *data)
{
	int	a;

	a = 0;
	while (a < TEX_COUNT)
	{
		if (check_file(data->textures[a], 2) == 1)
		{
			if (load_xpm(data, a))
				return ((printf("Error\nFailed to load XMP texture %d: %s\n", \
				a, data->textures[a])), -1);
		}
		else if (check_file(data->textures[a], 2) == 2)
		{
			if (load_png(data, a))
				return ((printf("Error\nFailed to load PNG texture %d: %s\n", \
				a, data->textures[a])), -1);
		}
		a++;
	}
	return (0);
}

void	cleanup_textures(t_data *data)
{
	int	a;

	if (!data)
		return ;
	a = 0;
	while (a < TEX_COUNT)
	{
		if (data->load_textures[a].loaded)
		{
			if (data->load_textures[a].xpm)
			{
				mlx_delete_xpm42(data->load_textures[a].xpm);
				data->load_textures[a].xpm = NULL;
			}
			else if (data->load_textures[a].tex)
				mlx_delete_texture(data->load_textures[a].tex);
			data->load_textures[a].tex = NULL;
			data->load_textures[a].loaded = 0;
		}
		a++;
	}
}
