/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/20 17:31:52 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>
# include <minirt_define.h>
# include <rt_vector.h>
# include <rt_matrix.h>
// from black arts
// # include "black_globals.h"
# include "black3.h"
# include "black4.h"
# include "black11.h"
# include <search.h>             // this one is needed for qsort()


//  General setup functions
int		minirt(t_minirt *s);
// int		render(t_minirt *s);
int		setup_mlx(t_scene scene, t_camera cam);
bool	setup_rayt(t_minirt *s);
bool	setup_menu(t_minirt *s);
int		setup_hooks(t_minirt *s);
int		render_rayt(t_minirt *s);
int		render_menu(t_minirt *s);
void	clear_rayt(t_minirt *s);

//	hooks.c
int		handle_keypress(int keysym, t_minirt *s);
int		more_keypress(int keysym, t_minirt *s);
int		handle_buttons(int button, int x, int y, t_minirt *s);
int		mouse_rayt(int button, int x, int y, void *p);
int		mouse_menu(int button, int x, int y, void *p);

//	mlx_aux.c
void	pixel_put(t_img *img, int x, int y, int color);
void	pixel_put_alpha(t_img *img, int x, int y, int color);
int		render_rect(t_img *img, t_rect rect);
void	pixel_put_black(t_img *img, int index, int color);
void	pixel_put_circle(t_img *img, t_circle c, int x, int y);
// int		render_rect(t_img *img, t_rect rect);
void	set_bk_color(char *data, int color, size_t size);
int		other_circle(t_img img, t_circle circle);
void	draw_circle(t_img img, t_circle circle);
void	draw_circle_fill(t_img img, t_circle circle);
void	draw_radio(t_minirt *s, t_circle circle, char *text, bool on_off);

// parsing
int		parser(t_scene *scene, t_camera *cam, char *file);
int		parse_cam(t_camera *cam, char *line);
int		(*parse_scene_elem(char *line))(t_scene *scene, char *line);
int		parse_ambience(t_scene *scene, char *line);
int		parse_light(t_scene *scene, char *line);
int		parse_sphere(t_scene *scene, char *line);
int		parse_plane(t_scene *scene, char *line);
int		parse_cylinder(t_scene *scene, char *line);
int		check_needed_elements(t_camera cam, t_scene scene, char *file);
int		parse_point(float (*point)[3], char *line, int vector);
int		parse_color(t_pixel *c, char *line);
void	skip_info(char **line);
int		in_range(float target, float min, float max);

// ray tracing

// shader aux
void	rgb_color(t_pixel *color, float surface_normal[3]);
void	draw_line(t_minirt *s, int o[2], int d[2], int color);
void	init_obb(t_obb	*obb, t_sphere object);
void	init_obb_pos(t_obb *obb, float min[3], float max[3]);
void	init_vertex_list(t_obb	*obb);
t_obb	draw_obb(t_minirt *s, t_sphere object, int color);
float	*init_zbuffer(size_t size);
void	*ft_memsetf(void *s, float f, size_t n);
bool	is_closer(float *z_buffer, float z, int index);
// memory handle
void	free_scene(t_scene *scene);
int		end_minirt(t_minirt *s);

#endif
