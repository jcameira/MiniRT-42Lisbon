/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/17 17:47:23 by cjoao-de         ###   ########.fr       */
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
# include <minirt_typedef.h>
# include <minirt_define.h>
# include <rt_vector.h>
# include <rt_matrix.h>
# include <rt_bvh.h>
// from black arts
// # include "black_globals.h"
// # include "black3.h"
// # include "black4.h"
// # include "black11.h"
// # include <search.h>             // this one is needed for qsort()

# include <debug.h>

//  General setup functions
int		minirt(t_minirt *s);
// int		render(t_minirt *s);
int		setup_mlx(t_scene scene, t_camera cam);
bool	setup_rayt(t_minirt *s);
bool	setup_menu(t_minirt *s);
int		setup_hooks(t_minirt *s);
int		render_rayt(t_minirt *s);
int		render_menu(t_minirt *s);

bool	load_menu_asset(t_minirt *s, t_img *asset, char *filename);

void	clear_rayt(t_minirt *s);
////////////////	TEMP	///////////////
bool	quad_test(void);
void	quad_init(t_quad *q, const float Q[3], const float u[3], const float v[3], t_pixel color);
bool	quad_hit(const t_quad *q, const float ray_origin[3], const float ray_dir[3], float *t_out);

//	hooks.c
int		handle_keypress(int keysym, t_minirt *s);
// int		more_keypress(int keysym, t_minirt *s);
// int		handle_buttons(int button, int x, int y, t_minirt *s);
int		mouse_rayt(int button, int x, int y, void *p);
int		mouse_menu(int button, int x, int y, void *p);
//	hooks_aux.c
void	render_bt(t_minirt *p);
void	radio_one(t_minirt *p);
void	color_picker(t_minirt *p, int x, int y);

//RGB_aux
t_pixel	get_rgb(int color);
t_pixel	color(float r, float g, float b);

//	mlx_aux.c0.000000,-100.500000,-1.000000

void	pixel_put(t_img *img, int x, int y, int color);
void	pixel_put_alpha(t_img *img, int x, int y, int color);
// void	pixel_put_black(t_img *img, int index, int color);
void	set_bk_color(char *data, int color, size_t size);
void	join_xpm_img(t_img img, t_img xpm, int x, int y);
void	dup_image(t_minirt *s);
void	restore_image(t_minirt *s);

// draw 2d utils
t_coord	project_normalized_vec3(const vec3 vec);
int		render_rect(t_img *img, t_rect rect);
void	draw_circle(t_img img, t_circle circle);
void	draw_circle_fill(t_img img, t_circle circle);
void	draw_radio(t_minirt *s, t_circle circle, char *text, bool on_off);
void 	draw_line(t_minirt *s, t_line line);

//? static
// void	init_line(t_line *line);
// void	line_down(t_line *line);
// void	line_up(t_line *line);
// void	pixel_put_circle(t_img *img, t_circle c, int x, int y);

// Bounding box
// t_bbox	sphere_bbox(const hittable* h);
void	sphere_bbox(t_figure *new_f);
// void	init_bbox(t_bbox *bbox, t_sphere *object);
void	init_bbox(t_bbox *obb, float min[3], float max[3]);
// void	init_bbox_pos(t_bbox *bbox, float min[3], float max[3]);	//? static
// void	init_vertex_list(t_bbox	*bbox);	//? static
// t_bbox	draw_obb(t_minirt *s, t_sphere object, int color);
void	draw_obb(t_minirt *s, t_bbox *obb, int color);

// Z-buffer
float	*init_zbuffer(size_t size);
bool	is_closer(float *z_buffer, float z, int index);

// ft_aux
void	toogle_bool(bool *toggle);
int		count_lines(int fd);

// parsing
int		parser(t_scene *scene, t_camera *cam, char *file);
int		parse_cam(t_camera *cam, char *line);
int		(*parse_scene_elem(char *line))(t_scene *scene, char *line);
int		parse_ambience(t_scene *scene, char *line);
int		parse_light(t_scene *scene, char *line);
int		parse_sphere(t_scene *scene, char *line);
int		parse_plane(t_scene *scene, char *line);
int		parse_cylinder(t_scene *scene, char *line);
int		parse_quad(t_scene *scene, char *line);
int		check_needed_elements(t_camera cam, t_scene scene, char *file);
int		parse_point(float (*point)[3], char *line, int vector);
int		parse_color(t_pixel *c, char *line);
void	skip_info(char **line);
int		in_range(float target, float min, float max);

// ray tracing
// textures
t_pixel	texture_solid_color(const t_texture *texture, float u, float v, const float p[3]);
t_pixel	texture_checker(const t_texture *texture, float u, float v, const float p[3]);
t_pixel	texture_image(const t_texture *texture, float u, float v, const float p[3]);
float	random_float_in_interval(float min, float max);
void	random_on_hemisphere(float new_direction[3], float normal[3]);
t_pixel	mult_color(t_pixel color, t_pixel attenuation);
t_ray	get_ray(float origin[3], float direction[3]);
t_pixel	ray_color(t_minirt *s, t_ray ray, int depth);
void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info);

// Rays
t_ray	get_ray(float origin[3], float direction[3]);
t_pixel	ray_color(t_minirt *s, t_ray ray, int depth);
t_pixel	color(float r, float g, float b);
void	gamma_correction(t_pixel *color);
t_pixel	attenuate_color(t_pixel color, t_pixel attenuation);
void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info);

// Anti Aliasing
void	add_pixel_color(t_pixel *real_p, t_pixel to_add);
void	anti_aliasing_get_color(t_pixel *real_p);

// Object intersections
int		hit_sp(t_ray *ray, float ray_max, t_hitrecord *hit_info,
			t_sphere sphere);
int		hit_pl(t_ray *ray, float ray_max, t_hitrecord *hit_info,
			t_plane plane);
int		hit_cy(t_ray *ray, float ray_max, t_hitrecord *hit_info,
			t_cylinder cylinder);
int		find_hittable(t_minirt *s, t_ray *ray, float ray_max,
			t_hitrecord *hit_info);

// Random
float	random_float(void);
float	random_float_in_interval(float min, float max);
void	random_on_hemisphere(float new_direction[3], float normal[3]);

// memory handle
void	free_scene(t_scene *scene);
int		end_minirt(t_minirt *s);

//! function graveyard
void	rgb_color(t_pixel *color, float surface_normal[3]);
void	get_real_color(t_pixel *real_p);
int		hit_sphere(t_ray *ray, float ray_max, t_hitrecord *hit_info, t_figure *tmp);


#endif
