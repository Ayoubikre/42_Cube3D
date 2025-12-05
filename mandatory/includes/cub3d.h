/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noctis <noctis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:34:32 by anktiri           #+#    #+#             */
/*   Updated: 2025/12/05 02:51:09 by noctis           ###   ########.fr       */
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

int				main(int ac, char **av);

// -------------------------------------------- Parsing:

int				parse_file(char *filename, t_data *data);
int				check_file(char *filename, int flag);

int				parse_texture_line(char *line, t_data *data, int f);
int				parse_color_line(char *line, t_data *data);
int				parse_rgb(char *str, t_color *color);

int				is_texture_line(char *line);
int				is_element_line(char *line);
int				is_map_line(char *line);

int				parse_map(int fd, t_data *data, char *first_line);
int				store_map_line(t_data *data, char *line);

int				validate_map(t_data *data);
int				check_map_closed(t_data *data);
int				check_map_characters(t_data *data);
int				find_player(t_data *data);
int				validate_elements_complete(t_data *data);
int				all_elements_parsed(t_data *data);

int				is_empty_line(char *line);
char			*skip_spaces(char *str);
int				is_map_char(char c);
int				ft_isspace(char c);
void			set_player_data(t_data *data, int i, int j);
char			get_char_at(t_data *data, int y, int x);
int				is_valid_pos(char c);
int				is_player_char(char c);

int				parse_lvl_line(char *line, t_data *data);
int				is_lvl_line(char *line);

void			print_error(char *msg);

// -------------------------------------------- Game:

void			draw_background(t_game *game, t_data *data);
double			norm_pi(double a);
void			put_px(mlx_image_t *img, int x, int y, uint32_t color);

void			calculate_wall_projection(t_data *data, t_render_vars *vars);
double			calculate_wall_x(t_data *data, t_render_vars *vars);
int				calculate_texture_x(t_data *data, t_render_vars *vars,
					double wallX, int tex_index);
void			draw_column_pixels(t_game *game, t_render_vars *vars,
					int tex_index, int tex_x);
int				get_text_index(t_ray *ray);
uint32_t		get_fallback_color(int tex_index);
uint32_t		get_texture_pixel(t_data *data, int tex_index, int x, int y);
void			ft_render_column(t_game *game, t_data *data,
					t_render_vars *vars);
void			cleanup_textures(t_data *data);
void			ft_render3d(t_game *game, t_data *data);
int				ft_init_textures(t_data *data);

//-------

int				ft_wrap_start_game(t_game *game);
void			ft_start_game(t_game *game);
void			ft_hooks(t_game *game);
void			ft_all(void *param);

int				ft_wrap_main_core(t_game *game, char *path);
int				ft_main_core(t_data *data, char *file_name);
int				ft_insert_dome_data(t_data *data);
void			ft_set_player_data_bak(t_data *data);

int				ft_init_lvl(t_game *game, t_data *data);
void			ft_destroy_lvl(t_game *game, t_data *data, int f);
int				ft_init_mlx_minimap(t_game *game, t_data *data);
int				ft_init_mlx_map(t_game *game);
void			ft_reset_player_data(t_data *data);

void			ft_capture_player_moves(t_game *game, t_data *data);
void			ft_capture_player_rot(t_game *game, t_data *data);
int				ft_move(t_data *data, double move_x, double move_y, double r);
int				ft_padding(t_data *data, double x, double y);
int				ft_find_walls(t_data *data, int x, int y);
void			ft_update_mouse_angle(double xpos, double ypos, void *param);
void			ft_speed(t_game *game, t_data *data);

void			ft_raycasting(t_data *data);
void			ft_dda(t_data *data, t_ray *ray);
void			ft_set_info(t_ray *ray, char w);
void			ft_first_cell_len(t_data *data, t_ray *ray);
void			ft_init_ray_data(t_data *data, t_ray *ray, int i, double r);

t_levels		*ft_creat_new_list(char *path);
void			ft_add_list_end(t_levels **lvls, t_levels *n);
int				ft_list_count(t_levels *lvls);

void			ft_capture_keys(mlx_key_data_t keydata, void *param);
void			ft_open_and_close_doors(t_data *data, int f);

void			ft_switch_lvl(t_game *game, t_data *data);
void			ft_draw_level_text(t_game *game);

void			ft_free_mlx(t_game *game);
void			ft_free_map(t_map *map);
void			ft_free_data(t_data *data);
void			ft_free_lvl(t_levels *lvl);
void			ft_free_list(t_game *game);

char			*ft_strjoin3(char *s1, char *s2, char *s3);
unsigned int	ft_color(t_color clr);
double			ft_rad(double x);
double			ft_deg(double x);

void			ft_minimap(t_game *game, t_data *data);

void			ft_start_animation(t_game *game, t_data *data);
void			ft_switch_animation(t_game *game, t_data *data);
void			ft_dead_animation(t_game *game, t_data *data);
void			ft_end_animation(t_game *game, t_data *data);

// ------- remove later :

void			ft_draw_player_2d(t_game *game, t_data *data, uint32_t px,
					uint32_t py);
void			ft_draw_map_2d(t_game *game, t_data *data, uint32_t px,
					uint32_t py);
void			ft_draw_background(t_game *game, t_data *data, uint32_t px,
					uint32_t py);
void			ft_draw_ray(t_game *game, t_data *data, double angle,
					double ray_len);
void			print_parse_results(t_data *data);
void			print_game(t_game *game);

#endif