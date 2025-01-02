/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/02 15:47:49 by jcameira         ###   ########.fr       */
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
# include <limits.h>
# include <libft.h>
# include <mlx.h>
# include <mlx_int.h>
# include <minirt_define.h>
# include <rt_vector.h>
# include <rt_matrix.h>

//  General setup functions
int		minirt(t_minirt *s);
int		render(t_minirt *s);
int		setup_mlx(t_scene scene, t_camera cam);
int		setup_hooks(t_minirt *s);

//	Hooks.c
int		setup_hooks(t_minirt *s);
int		handle_keypress(int keysym, t_minirt *s);
int		more_keypress(int keysym, t_minirt *s);
int		handle_buttons(int button, int x, int y, t_minirt *s);

//	Mlx_aux.c
void	pixel_put(t_img *img, int x, int y, int color);
void	pixel_put_alpha(t_img *img, int x, int y, int color);
int		render_rect(t_img *img, t_rect rect);

// Parsing
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

// Memory handle
void	free_scene(t_scene *scene);
int		end_minirt(t_minirt *s);

// Random
float	random_float(void);
float	random_float_in_interval(float min, float max);
void	random_on_hemisphere(float new_direction[3], float normal[3]);

#endif
