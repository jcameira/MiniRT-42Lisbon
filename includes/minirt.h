/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:24:26 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/25 05:05:46 by jcameira         ###   ########.fr       */
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

# include <debug.h>

//  General setup functions
int		minirt(t_minirt *s);
// int		render(t_minirt *s);
void	calc_viewport_info(t_scene *scene);
int		setup_mlx(t_scene scene);
bool	setup_rayt(t_minirt *s);
bool	setup_menu(t_minirt *s);
int		setup_hooks(t_minirt *s);
int		render_rayt(t_minirt *s);
int		render_menu(t_minirt *s);

bool	load_menu_asset(t_minirt *s, t_img *asset, char *filename);

void	clear_rayt(t_minirt *s);

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
t_pixel	add_pixel_color(t_pixel real_p, t_pixel to_add);
t_pixel	scale_pixel_color(t_pixel real_p, float scalar);

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

// ft_aux
void	toogle_bool(bool *toggle);
int		count_lines(int fd);

// Parsing
int		parser(t_scene *scene, char *file);
int		parse_cam(t_scene *cam, char *line);
int		(*parse_scene_elem(char *line))(t_scene *scene, char *line);
int		parse_ambience(t_scene *scene, char *line);
int		parse_light(t_scene *scene, char *line);
int		parse_sphere(t_scene *scene, char *line);
int		parse_plane(t_scene *scene, char *line);
int		parse_cylinder(t_scene *scene, char *line);
int		parse_quad(t_scene *scene, char *line);
int		check_needed_elements(t_scene scene, char *file);
int		parse_point(float (*point)[3], char *line, int vector);
int		parse_color(t_pixel *c, char *line);
int		parse_material(t_material *mat, char *line);
void	skip_info(char **line);
int		in_range(float target, float min, float max);

// Rays
t_ray	get_ray(float origin[3], float direction[3]);
t_pixel	ray_color(t_scene *scene, t_ray ray, int depth);
t_pixel	color(float r, float g, float b);
void	gamma_correction(t_pixel *color);
void	set_face_normal(float ray_direction[3], t_hitrecord *hit_info);

// Anti Aliasing
void	anti_aliasing_get_color(t_pixel *real_p);

// Random
float	random_float(void);
float	random_float_in_interval(float min, float max);
int		random_int_in_interval(int min, int max);
void	random_unit_vector(float new_direction[3]);
void	random_on_hemisphere(float new_direction[3], float normal[3]);

// Object intersections
//int		hit_sp(t_ray *ray, float *ray_t, t_hitrecord *hit_info,
//    t_sphere sphere);
float	hit_sp(t_list *obj, t_ray *ray, float min, float max);
int		hit_pl(t_ray *ray, float *ray_t, t_hitrecord *hit_info,
	t_plane plane);
int		hit_cy(t_ray *ray, float *ray_t, t_hitrecord *hit_info,
	t_cylinder cylinder);
int		find_hittable(t_list *objects, t_ray *ray, t_hitrecord *hit);

// Object Normals
void	normal_sp(t_list *obj, t_hitrecord *hit);

// Scatters
t_ray	lambertian_scatter(t_ray *in_r, t_hitrecord *hit);
t_ray	specular_scatter(t_ray *in_r, t_hitrecord *hit);

// Memory Handle
void	free_arr(void **arr);
void	free_scene(t_scene *scene);
int		end_minirt(t_minirt *s);

// Object Utilities
t_list	    *new_object(void);
t_object	*object_content(t_list *object);
t_material	object_material(t_list *object);
t_pixel		object_color(t_list *object);

// Light Utilities
t_list	    *new_light(void);
t_light	    *light_content(t_list *object);

#endif
