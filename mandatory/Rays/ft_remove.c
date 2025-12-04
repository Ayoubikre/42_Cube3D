/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:55:49 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 02:03:12 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//----------------------------------------------
//------------------------------ player draw 2D:
//----------------------------------------------


#include "../includes/cub3d.h"


void	ft_draw_player_2d(t_game *game,t_data *data, uint32_t px, uint32_t py)
{
	int (s), (player_px), (player_py), (j), i = -1;
	s = (int)fmax(data->map.cell_s / 8, 4);
	player_px = data->player.pos_x * data->map.cell_s;
	player_py = data->player.pos_y * data->map.cell_s;
	while (++i <= s * 2)
	{
		j = -1;
		while (++j <= s * 2)
		{
			px = (player_px - s) + i;
			py = (player_py - s) + j;
			mlx_put_pixel(game->mlx.ptr_img, px, py, 0x000000);
		}
	}
	mlx_put_pixel(game->mlx.ptr_img, player_px, player_py, 0xFFFFFF);
}

//----------------------------------------------
//------------------------------ map draw 2D :
//----------------------------------------------

void	ft_draw_map_2d(t_game *game,t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			i = -1;
			while (++i < data->map.cell_s)
			{
				j = -1;
				while (++j < data->map.cell_s)
				{
					px = x * data->map.cell_s + i;
					py = y * data->map.cell_s + j;
					if (data->map.grid[y][x] == '1')
						mlx_put_pixel(game->mlx.ptr_img, px, py, 0x350707A1);
					else if (data->map.grid[y][x] == '2')
						mlx_put_pixel(game->mlx.ptr_img, px, py, 0xA507A7A1);
					else if (data->map.grid[y][x] == '4')
						mlx_put_pixel(game->mlx.ptr_img, px, py, 0xFF07AFA1);
					else
						mlx_put_pixel(game->mlx.ptr_img, px, py, 0xF5DEB388);
				}
			}
		}
	}
}

//----------------------------------------------
//------------------------------ Bg draw :
//----------------------------------------------

void	ft_draw_background(t_game *game,t_data *data, uint32_t px, uint32_t py)
{
	int (i), (j), (y), x = -1;
	while (++x < data->map.grid_x)
	{
		y = -1;
		while (++y < data->map.grid_y)
		{
			i = -1;
			while (++i < data->map.cell_s)
			{
				j = -1;
				while (++j < data->map.cell_s)
				{
					px = x * data->map.cell_s + i;
					py = y * data->map.cell_s + j;
					if (y < data->map.grid_y / 2)
						mlx_put_pixel(game->mlx.ptr_img, px, py,
							ft_color(data->ceiling_color));
					else
						mlx_put_pixel(game->mlx.ptr_img, px, py,
							ft_color(data->floor_color));
				}
			}
		}
	}
}

//----------------------------------------------
//------------------------------ Draw Rays :
//----------------------------------------------

void	ft_draw_ray(t_game *game,t_data *data, double angle, double ray_len)
{
    int x0 = (int)((data->player.pos_x * data->map.cell_s)) ;
    int y0 = (int)((data->player.pos_y * data->map.cell_s));
    double len_in_pixels = (ray_len ) * data->map.cell_s;
	int	x1 = (int)(x0 + cos(angle) * len_in_pixels);
	int	y1 = (int)(y0 + sin(angle) * len_in_pixels);
    int dx = abs(x1 - x0);
    int sx = (x0 < x1) ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    int e2;
    while (1)
    {
		mlx_put_pixel(game->mlx.ptr_img, x0, y0, 0x500075FF);
        if (x0 == x1 && y0 == y1)
            break ;
        e2 = 2 * err;
        if (e2 >= dy){
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            err += dx;
            y0 += sy;
        }
    }
}

//----------------------------------------------
//------------------------------ Print Map :
//----------------------------------------------

void	print_map(t_data *data)
{
	int	i;

	printf("\nMAP GRID:\n");
	i = 0;
	while (i < data->map.grid_y)
	{
		printf("  [%d] '%s'\n", i, data->map.grid[i]);
		i++;
	}
}

void	print_parse_results(t_data *data)
{
	printf("\n✓ Parsing Complete!\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("TEXTURES:\n");
	printf("  North:  %s\n", data->textures[NORTH]);
	printf("  South:  %s\n", data->textures[SOUTH]);
	printf("  West:   %s\n", data->textures[WEST]);
	printf("  East:   %s\n", data->textures[EAST]);
	printf("  Door:   %s\n", data->textures[DOOR]);
	printf("  Portal:   %s\n", data->textures[PORTAL]);
	printf("\nPATH:\n");
	printf("  Next lvl Path:   %s\n", data->next_file);
	printf("\nCOLORS:\n");
	printf("  Floor:   RGB(%d, %d, %d)\n", data->floor_color.r,
		data->floor_color.g, data->floor_color.b);
	printf("  Ceiling: RGB(%d, %d, %d)\n", data->ceiling_color.r,
		data->ceiling_color.g, data->ceiling_color.b);
	printf("\nMAP INFO:\n");
	printf("  Size: %dx%d\n", data->map.grid_x, data->map.grid_y);
	printf("  Player: (%.1f, %.1f) facing '%c'\n", data->player.pos_x,
		data->player.pos_y, data->player.orientation);
	print_map(data);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}
