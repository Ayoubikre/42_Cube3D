/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aakritah <aakritah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/10/24 21:54:01 by aakritah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_draw_map_2D(t_data *data)
{
    int x;
    int y;
    int i;
    int j;

    int cell_w = WIDTH / data->map.width;
    int cell_h = HEIGHT / data->map.height;

    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.width)
        {
            char cell = data->map.grid[y][x];
            unsigned int color;

            if (cell == '1')
                color = 0x800000A1; 
            else
                color = 0xC0C0C0A1;

            i = 0;
            while (i < cell_h)
            {
                j = 0;
                while (j < cell_w)
                {
                    int px = x * cell_w + j;
                    int py = y * cell_h + i;
                    mlx_put_pixel(data->mlx.ptr_img, px, py, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}
 
void ft_all(void *param)
{
    t_data* data;

    data= (t_data*) param;
    ft_draw_map_2D(data);
    
}

int ft_start(t_data* data)
{
    data->mlx.ptr=mlx_init(WIDTH, HEIGHT, "Cube3D", false);
    if(!data->mlx.ptr)
        return -1;
    
    data->mlx.ptr_img=mlx_new_image(data->mlx.ptr,WIDTH,HEIGHT);
    if(!data->mlx.ptr_img)
        return -1;
    
    data->mlx.idx=mlx_image_to_window(data->mlx.ptr,data->mlx.ptr_img,0,0);
    if(data->mlx.idx==-1)
        return -1;
    
    
    mlx_loop_hook(data->mlx.ptr,ft_all,(void*)data);
    mlx_loop(data->mlx.ptr);
    mlx_delete_image(data->mlx.ptr, data->mlx.ptr_img);
    mlx_terminate(data->mlx.ptr); 
    return 0;
}
