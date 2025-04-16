/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 07:24:26 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 15:52:36 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// # include <unistd.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <stdbool.h>
// # include <fcntl.h>
// # include <float.h>
// # include <limits.h>
//! all above are included with libft
# include <libft.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <minirt_typedef.h>
# include <minirt_define.h>
# include <rt_vector.h>
# include <rt_matrix.h>

//	MAIN FUNCTIONS
int			minirt(t_minirt *s);
int			render_rayt(t_minirt *s);
int			render_menu(t_minirt *s);

//  General setup functions
bool		setup_rayt(t_minirt *s);
bool		setup_menu(t_minirt *s);
bool		setup_assets(t_minirt *s);
bool		load_assets(t_minirt *s);
bool		load_image_asset(t_minirt *s, t_img_asset *asset, char *filename);

//	HOOKS
int			handle_keypress(int keysym, t_minirt *s);
int			setup_hooks(t_minirt *s);
// int		mouse_rayt(int button, int x, int y, void *p);
// int		more_keypress(int keysym, t_minirt *s);
// int		handle_buttons(int button, int x, int y, t_minirt *s);

//	MENU
int			menu_keys(int keysym, t_minirt *s);
int			menu_mouse(int button, int x, int y, void *param);
void		draw_color_picker(t_minirt *s);
void		draw_quality_picker(t_minirt *s);
void		draw_gradients(t_minirt *s);
void		draw_gradient_values(t_minirt *s);
void		draw_labels(t_minirt *s, int x, int y);
void		draw_help(t_minirt *s, int x, int y);
void		render_bt(t_minirt *p);
void		radio_one(t_minirt *p);
void		radio_two(t_minirt *p);
void		radio_three(t_minirt *p);
void		radio_four(t_minirt *p);
void		color_picker(t_minirt *p, int x, int y);
void		attribute_picker(t_minirt *p, int x, int y);
void		set_material(t_list *object, int keysym);
void		set_quality(t_minirt *s, int x);
// void		set_advanced_material(t_list *object, int keysym);
// void	draw_brightness_picker(t_minirt *s);
// void	brightness_picker(t_minirt *p, int x, int y);
// void	clear_rayt(t_minirt *s);
// char	*f_name(int idx);

//	MLX
void		pixel_put(t_img *img, int x, int y, int color);
void		set_bk_color(char *data, int color, size_t size);
void		join_xpm_img(t_img img, t_img_asset xpm, int x, int y);
void		join_xpm_sprite(t_img img, t_img_asset xpm, t_coord pos, int idx);
void		dup_image(char *dst, char *src);
void		restore_image(t_minirt *s, char *image);
//	RGB_aux
t_pixel		get_rgb(int color);
t_pixel		color(float r, float g, float b);
t_pixel		add_pixel_color(t_pixel real_p, t_pixel to_add);
t_pixel		scale_pixel_color(t_pixel real_p, float scalar);
t_pixel	    attenuate_color(t_pixel color, t_pixel attenuation);

//	ANAGLYPH
void		create_anaglyph(t_minirt *s);
void		create_right_eye(t_minirt *s);
void		create_left_eye(t_minirt *s);
// Dubois matrix (left and right)
float		drm(int row, int col);
float		dlm(int row, int col);

// DRAW 2D UTILS
int			render_rect(t_img *img, t_rect rect);
void		draw_circle(t_img img, t_circle c);
void		draw_circle_fill(t_img img, t_circle c);
void		draw_radio(t_minirt *s, t_circle c, char *text, bool on_off);
void		draw_line(t_img img, t_line line);

// ft_aux
void		toogle_bool(bool *toggle);

// Parsing
int			parser(t_scene *scene, char *file);
int			parse_cam(t_scene *cam, char *line);
int			(*parse_scene_elem(char *line))(t_scene *scene, char *line);
int			parse_ambience(t_scene *scene, char *line);
int			parse_default_light(t_scene *scene, char *line);
int			parse_sphere(t_scene *scene, char *line);
int			parse_plane(t_scene *scene, char *line);
int			parse_cylinder(t_scene *scene, char *line);
int			parse_quad(t_scene *scene, char *line);
int			parse_cone(t_scene *scene, char *line);
int			parse_disk(t_scene *scene, char *line);
int			check_needed_elements(t_scene scene, char *file);
int			parse_point(float (*point)[3], char *line, int vector);
int			parse_color(t_pixel *c, char *line);
int			parse_material(t_material *mat, char **line);
int			in_range(float target, float min, float max);
void	    cam_prepare_vp(t_scene *scene);
void		calc_viewport_info(t_scene *scene);

// Rays
t_ray		get_ray(float origin[3], float direction[3]);
t_pixel		ray_color(t_scene *scene, t_ray ray, int depth);
t_pixel		color(float r, float g, float b);
void		gamma_correction(t_pixel *color);
void		set_face_normal(float ray_direction[3], t_hitrecord *hit_info);

// Anti Aliasing
void		anti_aliasing_get_color(t_pixel *real_p, int rays);

// Random
float		random_float(void);
float		random_float_in_interval(float min, float max);
int			random_int_in_interval(int min, int max);
void		random_unit_vector(float new_direction[3]);
void		random_on_hemisphere(float new_direction[3], float normal[3]);

// Object intersections
float		hit_sp(t_list *obj, t_ray *ray, float min, float max);
float		hit_pl(t_list *obj, t_ray *ray, float min, float max);
float		hit_qu(t_list *obj, t_ray *ray, float min, float max);
float		hit_cy(t_list *obj, t_ray *ray, float min, float max);
float		hit_ds(t_list *obj, t_ray *ray, float min, float max);
float		hit_co(t_list *obj, t_ray *ray, float min, float max);
int			find_hittable(t_list *objects, t_ray *ray, t_hitrecord *hit);
void		get_sphere_uv(t_hitrecord *hit);

// Object Normals
int			normal_sp(t_list *obj, t_hitrecord *hit);
int			normal_pl(t_list *obj, t_hitrecord *hit);
int			normal_qu(t_list *obj, t_hitrecord *hit);
int			normal_cy(t_list *obj, t_hitrecord *hit);
int			normal_ds(t_list *obj, t_hitrecord *hit);
int			normal_co(t_list *obj, t_hitrecord *hit);

// Scatters
t_ray		lambertian_scatter(t_ray *in_r, t_hitrecord *hit);
t_ray		specular_scatter(t_ray *in_r, t_hitrecord *hit);
t_ray		dialetric_scatter(t_ray *in_r, t_hitrecord *hit);
t_ray		bump_scatter(t_ray *in_r, t_hitrecord *hit);
void		reflect(float *result, float *v, float *n);
float		reflectance(float cosine, float ri);
void		refract(float *result, float *v, float *n, float ri);

// Get Colors
t_pixel		object_color(t_list *obj, t_hitrecord *hit);
t_pixel		checkered_color(t_list *obj, t_hitrecord *hit);
t_pixel		image_color(t_list *obj, t_hitrecord *hit);
t_pixel		bump_color(t_list *obj, t_hitrecord *hit);

// Memory Handle
void		free_arr(void **arr);
void		free_scene(t_minirt *s);
int			end_minirt(t_minirt *s);

// Object Utilities
t_list		*new_object(void);
t_object	*object_content(t_list *object);
t_material	object_material(t_list *object);
t_ftype		object_type(t_list *object);

// Light Utilities
t_list		*new_light(void);
t_light		*light_content(t_list *object);

// Math
float		ft_fmin(float a, float b);

int			arr_size(char **arr);

int			check_if_float(char *arg);
int			check_if_int(char *arg);

#endif
