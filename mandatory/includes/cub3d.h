/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:34:32 by anktiri           #+#    #+#             */
/*   Updated: 2025/11/28 00:19:03 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../42_Libft/libft.h"
# include "Data.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# ifdef __linux__
#  include "../../Tools/mlx/linux/MLX42.h"
# else
#  include "../../Tools/mlx/macOS/MLX42.h"
# endif

int		main(int ac, char **av);

// -------------------------------------------- Parsing:

int		parse_file(char *filename, t_data *data);
int		main_core(t_data *data, char *file_name);

int		check_file(char *filename, int flag);

int		parse_texture_line(char *line, t_data *data);
int		parse_color_line(char *line, t_data *data);
int		parse_rgb(char *str, t_color *color);

int		is_texture_line(char *line);
int		is_element_line(char *line);
int		is_map_line(char *line);

int		parse_map(int fd, t_data *data, char *first_line);
int		store_map_line(t_data *data, char *line);

int		validate_map(t_data *data);
int		check_map_closed(t_data *data);
int		check_map_characters(t_data *data);
int		find_player(t_data *data);
int		validate_elements_complete(t_data *data);
int		all_elements_parsed(t_data *data);

int		is_empty_line(char *line);
char	*skip_spaces(char *str);
int		is_map_char(char c);
int		ft_isspace(char c);
void	set_player_data(t_data *data, int i, int j);
char	get_char_at(t_data *data, int y, int x);
int		is_valid_pos(char c);
int		is_player_char(char c);

void	print_error(char *msg);
void	free_data(t_data *data);
void	free_map(t_map *map);

void	init_data(t_data *data);

// -------------------------------------------- Raycasting:

void		draw_background(t_data *data);
double		norm_pi(double a);
void		put_px(mlx_image_t *img, int x, int y, uint32_t color);

void		calculate_wall_projection(t_data *data, t_render_vars *vars);
double		calculate_wall_x(t_data *data, t_render_vars *vars);
int			calculate_texture_x(t_data *data, t_render_vars *vars, double wallX, int tex_index);
void		draw_column_pixels(t_data *data, t_render_vars *vars, int tex_index, int texX);
int			get_text_index(t_ray *ray);
uint32_t	get_fallback_color(int tex_index);
uint32_t	get_texture_pixel(t_data *data, int tex_index, int x, int y);

void			ft_render_column(t_data *data, t_render_vars *vars);
void			cleanup_textures(t_data *data);
void			ft_render3d(t_data *data);
int				ft_init_textures(t_data *data);
unsigned int	ft_color(t_color clr);
double			ft_rad(double x);
double			ft_deg(double x);
int				ft_start(t_data *data);

#endif