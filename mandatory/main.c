/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akzaza <akzaza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:15:00 by anktiri           #+#    #+#             */
/*   Updated: 2025/10/19 15:09:28 by akzaza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		data->textures[i] = NULL;
		i++;
	}
	data->floor_color = (t_color){0, 0, 0};
	data->ceiling_color = (t_color){0, 0, 0};
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.orientation = 0;
	i = 0;
	while (i < ELEM_COUNT)
	{
		data->parsed[i] = 0;
		i++;
	}
}

int	all_elements_parsed(t_data *data)
{
	int	i;

	i = 0;
	while (i < ELEM_COUNT)
	{
		if (data->parsed[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	print_map(t_data *data)
{
	int	i;

	printf("\nMAP GRID:\n");
	i = 0;
	while (i < data->map.height)
	{
		printf("  [%d] '%s'\n", i, data->map.grid[i]);
		i++;
	}
}

static void	print_parse_results(t_data *data)
{
	printf("\n✓ Parsing Complete!\n");
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
	printf("TEXTURES:\n");
	printf("  North:  %s\n", data->textures[NORTH]);
	printf("  South:  %s\n", data->textures[SOUTH]);
	printf("  West:   %s\n", data->textures[WEST]);
	printf("  East:   %s\n", data->textures[EAST]);
	printf("\nCOLORS:\n");
	printf("  Floor:   RGB(%d, %d, %d)\n",
		data->floor_color.r, data->floor_color.g, data->floor_color.b);
	printf("  Ceiling: RGB(%d, %d, %d)\n",
		data->ceiling_color.r, data->ceiling_color.g, data->ceiling_color.b);
	printf("\nMAP INFO:\n");
	printf("  Size: %dx%d\n", data->map.width, data->map.height);
	printf("  Player: (%.1f, %.1f) facing '%c'\n",
		data->player.pos_x, data->player.pos_y, data->player.orientation);
	print_map(data);
	printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return ((print_error("Usage: ./cub3D <map.cub>")), 1);
	init_data(&data);
	if (!check_file(argv[1], 1))
	{
		print_error("Invalid file extension (must be .cub)");
		return (1);
	}
	if (!parse_file(argv[1], &data))
	{
		free_data(&data);
		return (1);
	}
	print_parse_results(&data);
	free_data(&data);
	return (0);
}
