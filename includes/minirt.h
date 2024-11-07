/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/11/06 14:18:07 by cjoao-de         ###   ########.fr       */
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
# include "../black/chap_11/black3.h"
# include "../black/chap_11/black4.h"
# include "../black/chap_11/black11.h"
# include <search.h>             // this one is needed for qsort()

//  General setup functions
int		minirt(t_minirt *s, char *argv1);
int		render(t_minirt *s, char *argv1);
// int		setup_mlx(t_scene scene, t_camera cam);
int		setup_mlx(t_scene scene, t_camera cam, char *argv1);
int		setup_hooks(t_minirt *s);

//	hooks.c
int		handle_keypress(int keysym, t_minirt *s);
int		more_keypress(int keysym, t_minirt *s);
int		handle_buttons(int button, int x, int y, t_minirt *s);

//	mlx_aux.c
void	pixel_put(t_img *img, int x, int y, int color);
void	pixel_put_alpha(t_img *img, int x, int y, int color);
int		render_rect(t_img *img, t_rect rect);

// parsing
int	    parser(t_scene *scene, t_camera *cam, char *file);
int	    parse_cam(t_camera *cam, char *line);
int	    (*parse_scene_elem(char *line))(t_scene *scene, char *line);
int	    parse_ambience(t_scene *scene, char *line);
int	    parse_light(t_scene *scene, char *line);
int	    parse_sphere(t_scene *scene, char *line);
int	    parse_plane(t_scene *scene, char *line);
int	    parse_cylinder(t_scene *scene, char *line);
int	    check_needed_elements(t_camera cam, t_scene scene, char *file);
int	    parse_point(float (*point)[3], char *line, int vector);
int	    parse_color(char *line);
void	skip_info(char **line);
int	    in_range(float target, float min, float max);

// memory handle
void	free_scene(t_scene *scene);
int		end_minirt(t_minirt *s);

#endif
