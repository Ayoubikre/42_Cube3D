/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:55:49 by noctis            #+#    #+#             */
/*   Updated: 2025/12/04 18:34:17 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//----------------------------------------------
//------------------------------ player draw 2D:
//----------------------------------------------

#include "../includes/cub3d.h"

void	ft_draw_player_2d(t_game *game, t_data *data, uint32_t px, uint32_t py)
{
	int(s), (player_px), (player_py), (j), i = -1;
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

void	ft_draw_map_2d(t_game *game, t_data *data, uint32_t px, uint32_t py)
{
	int(i), (j), (y), x = -1;
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

void	ft_draw_background(t_game *game, t_data *data, uint32_t px, uint32_t py)
{
	int(i), (j), (y), x = -1;
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

void	ft_draw_ray(t_game *game, t_data *data, double angle, double ray_len)
{
	int		x0;
	int		y0;
	double	len_in_pixels;
	int		x1;
	int		y1;
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err;
	int		e2;

	x0 = (int)((data->player.pos_x * data->map.cell_s));
	y0 = (int)((data->player.pos_y * data->map.cell_s));
	len_in_pixels = (ray_len)*data->map.cell_s;
	x1 = (int)(x0 + cos(angle) * len_in_pixels);
	y1 = (int)(y0 + sin(angle) * len_in_pixels);
	dx = abs(x1 - x0);
	sx = (x0 < x1) ? 1 : -1;
	dy = -abs(y1 - y0);
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		mlx_put_pixel(game->mlx.ptr_img, x0, y0, 0x500075FF);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
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

//----------------------------------------------
//------------------------------ Print  :
//----------------------------------------------

static void	print_color(const char *name, t_color c)
{
	printf("%s:\n", name);
	printf("  r = %d\n", c.r);
	printf("  g = %d\n", c.g);
	printf("  b = %d\n\n", c.b);
}

static void	print_player(const char *name, t_player *p)
{
	printf("%s:\n", name);
	printf("  pos_x = %f\n", p->pos_x);
	printf("  pos_y = %f\n", p->pos_y);
	printf("  orientation = %c\n", p->orientation);
	printf("  mouse_l_p = %f\n\n", p->mouse_l_p);
}

static void	print_player_bak(const char *name, t_player_bak *p)
{
	printf("%s:\n", name);
	printf("  pos_x = %f\n", p->pos_x);
	printf("  pos_y = %f\n", p->pos_y);
	printf("  orientation = %c\n", p->orientation);
	printf("  mouse_l_p = %f\n", p->mouse_l_p);
	printf("  ang = %f\n\n", p->ang);
}

static void	print_map2(t_map *map)
{
	printf("Map:\n");
	printf("  grid_x = %d\n", map->grid_x);
	printf("  grid_y = %d\n", map->grid_y);
	printf("  cell_s = %d\n\n", map->cell_s);
	if (!map->grid)
	{
		printf("  grid = NULL\n\n");
		return ;
	}
	printf("  grid:\n");
	for (int y = 0; y < map->grid_y; y++)
		printf("    %s\n", map->grid[y]);
	printf("\n");
}

static void	print_textures(char **paths, t_texture *tex, int count)
{
	printf("Textures:\n");
	for (int i = 0; i < count; i++)
	{
		printf("  [%d] path: %s\n", i, paths[i] ? paths[i] : "NULL");
		printf("       loaded: %d, width: %u, height: %u, bytes_per_pixel: %d\n", tex[i].loaded, tex[i].width, tex[i].height, tex[i].bytes_per_pixel);
	}
	printf("\n");
}

static void	print_rays(t_ray *rays, int count)
{
	if (!rays)
	{
		printf("Rays = NULL\n\n");
		return ;
	}
	printf("Rays (first 10 shown if many):\n");
	for (int i = 0; i < count && i < 10; i++)
		printf("  Ray[%d]: x=%d y=%d len=%f hit=%d side=%d drc=%c\n", i,
			rays[i].x, rays[i].y, rays[i].len, rays[i].hit, rays[i].side,
			rays[i].drc);
	if (count > 10)
		printf("  ... (total rays: %d)\n", count);
	printf("\n");
}

static void	print_mini(t_mini *mini)
{
	printf("Minimap:\n");
	printf("  ptr_img = %p\n", mini->ptr_img);
	printf("  id_img = %d\n", mini->id_img);
	printf("  mini_w = %f\n", mini->mini_w);
	printf("  mini_h = %f\n", mini->mini_h);
	printf("  player_size = %d\n", mini->m_player_size);
	printf("  cell_size = %d\n\n", mini->m_cell_size);
}

static void	print_mlx(t_mlx *mlx)
{
	printf("MLX:\n");
	printf("  ptr = %p\n", mlx->ptr);
	printf("  ptr_img = %p\n", mlx->ptr_img);
	printf("  id_img = %d\n\n", mlx->id_img);
}

void	print_data(t_data *data)
{
	printf("=== DATA ===\n\n");
	printf("Parsed flags:\n");
	for (int i = 0; i < ELEM_COUNT; i++)
		printf("  parsed[%d] = %d\n", i, data->parsed[i]);
	printf("\n");
	print_textures(data->textures, data->load_textures, TEX_COUNT);
	print_color("Floor", data->floor_color);
	print_color("Ceiling", data->ceiling_color);
	print_map2(&data->map);
	print_player("Player", &data->player);
	print_player_bak("Player backup", &data->player_bak);
	print_mini(&data->mini);
	print_rays(data->rays, RAYS);
	printf("fov = %f\n", data->fov);
	printf("ang = %f\n", data->ang);
	printf("move_speed = %f\n\n", data->move_speed);
}

void	print_game(t_game *game)
{
	if (!game)
	{
		printf("Game = NULL\n\n");
		return ;
	}
	printf("=== GAME ===\n\n");
	print_mlx(&game->mlx);
	printf("id_max = %d\n", game->id_max);
	printf("g_state = %d\n\n", game->g_state);
	if (!game->c_lvl)
	{
		printf("No current level\n\n");
		return ;
	}
	printf("Current level:\n");
	printf("  id = %d\n", game->c_lvl->id);
	printf("  path = %s\n\n", game->c_lvl->path ? game->c_lvl->path : "NULL");
	print_data(&game->c_lvl->data);
}
