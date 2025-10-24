/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 09:42:24 by noctis            #+#    #+#             */
/*   Updated: 2025/10/24 10:33:48 by noctis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (a << 24 | b << 16 | g << 8 | r);
}

void ft_update(void* param)
{
    mlx_t* mlx = param;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
        mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
        image->instances[0].y -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
        image->instances[0].y += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
        image->instances[0].x -= 5;
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
        image->instances[0].x += 5;

    for (uint32_t i = 0; i < image->width; ++i)
    {
        for (uint32_t y = 0; y < image->height; ++y)
        {
            uint32_t color = ft_pixel(
                rand() % 0xFF, rand() % 0xFF, rand() % 0xFF, 0xFF
            );
            mlx_put_pixel(image, i, y, color);
        }
    }
}

int ft_raycast(t_data* data)
{
    srand(time(NULL));

    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!mlx)
        return (puts(mlx_strerror(mlx_errno)), EXIT_FAILURE);

    image = mlx_new_image(mlx, 128, 128);
    if (!image)
        return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx), EXIT_FAILURE);

    if (mlx_image_to_window(mlx, image, 0, 0) == -1)
        return (puts(mlx_strerror(mlx_errno)), mlx_terminate(mlx), EXIT_FAILURE);

    mlx_loop_hook(mlx, ft_update, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}

