/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:06:30 by noctis            #+#    #+#             */
/*   Updated: 2025/12/10 17:17:10 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static uint32_t	get_minimap_color(char c)
// {
// 	if (c == '1')
// 		return (0x808080FF);
// 	if (c == '0' || is_player_char(c) || c == '3')
// 		return (0xFFFFFFFF);
// 	if (c == '2')
// 		return (0xFF0000FF);
// 	if (c == '4')
// 		return (0x00FF00FF);
// 	return (0x000000FF);
// }

// static void	draw_minimap_cell(t_data *d, int sx, int sy, char cell)
// {
// 	int			px;
// 	int			py;
// 	uint32_t	color;

// 	color = get_minimap_color(cell);
// 	py = 0;
// 	while (py < d->mini.cell_size)
// 	{
// 		px = 0;
// 		while (px < d->mini.cell_size)
// 		{
// 			put_px(d->mini.ptr_img, sx + px, sy + py, color);
// 			px++;
// 		}
// 		py++;
// 	}
// }


// static void	draw_minimap_grid(t_data *d)
// {
// 	int	sx, sy, ex, ey;
// 	int	map_x, map_y;
// 	int	pxx, pyy;


// 	map_y = sy;
// 	pyy = 0;
// 	while (map_y < ey && pyy < (int)d->mini.height)
// 	{
// 		map_x = sx;
// 		pxx = 0;
// 		while (map_x < ex && pxx < (int)d->mini.width)
// 		{
// 			draw_minimap_cell(d, pxx, pyy, get_char_at(d, map_y, map_x));
// 			pxx += d->mini.cell_size;
// 			map_x++;
// 		}
// 		pyy += d->mini.cell_size;
// 		map_y++;
// 	}
// }

// static void	draw_player_point(t_data *d)
// {
// 	int s = d->mini.width / 2;
// 	int e= d->mini.height / 2;
// 	int p = d->mini.p_size / 2;
// 	int px, py;

// 	py = e - p;
// 	while (py < e + p)
// 	{
// 		px = s - p;
// 		while (px < s + p)
// 		{
// 			put_px(d->mini.ptr_img, px, py, 0x000000FF);
// 			px++;
// 		}
// 		py++;
// 	}
// }

// void	ft_minimap(t_data *d)
// {
// 	if (!d->mini.ptr_img)
// 		return;
// 	draw_minimap_grid(d);
// 	draw_player_point(d);
// }



typedef struct s_norm
{
	int x_s;
	int y_s;
	int x_e;
	int y_e;
	int p_size;
	int px;
	int py;
	int i;
	int j;
}				t_norm;

static uint32_t	get_minimap_color(char c)
{
	if (c == '1')
		return (0x808080FF);
	if (c == '0' || is_player_char(c) || c == '3')
		return (0xFFFFFFFF);
	if (c == '2')
		return (0xFF0000FF);
	if (c == '4')
		return (0x00FF00FF);
	return (0x00000077);
}


void	ft_draw_cells(t_data *data, t_norm tmp, char c)
{
    int px;
    int py;
    
    py=0;
    while(py<data->mini.cell_size)
    {
        px=0;
        while(px<data->mini.cell_size)
        {
            put_px(data->mini.ptr_img,px+tmp.px, py+ tmp.py, get_minimap_color(c));
            px++;
        }
        py++;
    }
}

// void	ft_draw_map(t_data *data)
// {
//     t_norm tmp;
//     int cells_h = data->mini.height / data->mini.cell_size;
//     int cells_w = data->mini.width  / data->mini.cell_size;

//     int half_h = cells_h / 2;
//     int half_w = cells_w / 2;

//     tmp.y_s = (int)round(data->player.pos_y) - half_h;
//     tmp.x_s = (int)round(data->player.pos_x) - half_w;

//     tmp.y_e = tmp.y_s + cells_h - 1;
//     tmp.x_e = tmp.x_s + cells_w - 1;

//     tmp.py = 0;
//     for (int y = tmp.y_s; y <= tmp.y_e; y++) {
//         tmp.px = 0;
//         for (int x = tmp.x_s; x <= tmp.x_e; x++) {
//             ft_draw_cells(data, tmp, get_char_at(data, y, x));
//             tmp.px += data->mini.cell_size;
//         }
//         tmp.py += data->mini.cell_size;
//     }
// }

void	ft_draw_mapw(t_data *data)
{
    t_norm tmp;
    int cells_h = data->mini.height / data->mini.cell_size;
    int cells_w = data->mini.width  / data->mini.cell_size;

    int half_h = cells_h / 2;
    int half_w = cells_w / 2;

    tmp.y_s = (int)(data->player.pos_y) - half_h;
    tmp.x_s = (int)(data->player.pos_x) - half_w;

    tmp.y_e = tmp.y_s + cells_h - 1;
    tmp.x_e = tmp.x_s + cells_w - 1;

    tmp.py = 0;
    for (int y = tmp.y_s; y <= tmp.y_e; y++) {
        tmp.px = 0;
        for (int x = tmp.x_s; x <= tmp.x_e; x++) {
            ft_draw_cells(data, tmp, get_char_at(data, y, x));
            tmp.px += data->mini.cell_size;
        }
        tmp.py += data->mini.cell_size;
    }
}

void	ft_draw_map(t_data *data)
{
	t_norm	tmp;
    
    tmp.i=(int)((data->mini.height/ data->mini.cell_size) / 2);
	tmp.y_s = (int)data->player.pos_y - tmp.i;
	tmp.y_e = (int)data->player.pos_y + tmp.i;
    tmp.py=0;
    while(tmp.y_s<tmp.y_e)
    {
        tmp.j=(int)((data->mini.width / data->mini.cell_size) / 2);
        tmp.x_s = (int)data->player.pos_x - tmp.j;
        tmp.x_e = (int)data->player.pos_x + tmp.j;
        tmp.px=0;
        while(tmp.x_s <tmp.x_e)
        {
            ft_draw_cells(data, tmp, get_char_at(data, tmp.y_s, tmp.x_s));
            tmp.px += data->mini.cell_size;
            tmp.x_s++;
        }   
        tmp.py += data->mini.cell_size;
        tmp.y_s++;
    }
}



void	ft_draw_player(t_data *data)
{
	t_norm	tmp;

	tmp.x_s = data->mini.width / 2;
	tmp.y_s = data->mini.height / 2;
	tmp.p_size = data->mini.p_size / 2;
	tmp.py = tmp.y_s - tmp.p_size;
	while (tmp.py < tmp.y_s + tmp.p_size)
	{
		tmp.px = tmp.x_s - tmp.p_size;
		while (tmp.px < tmp.x_s + tmp.p_size)
		{
			put_px(data->mini.ptr_img, tmp.px, tmp.py, 0x000000FF);
			tmp.px++;
		}
		tmp.py++;
	}
}

void	ft_minimap(t_data *data)
{
	if (!data->mini.ptr_img)
		return ;
	ft_draw_map(data);
	ft_draw_player(data);
}