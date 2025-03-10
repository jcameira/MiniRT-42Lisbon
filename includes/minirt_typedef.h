/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/10 19:18:58 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPEDEF_H
# define MINIRT_TYPEDEF_H

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}				t_pixel;

typedef struct s_camera
{
	int			has_cam;
	float		o[3];
	float		nv[3];
	float		vup[3];
	float		u[3];
	float		v[3];
	float		w[3];
	int			fov;
	t_viewport	vp;
	t_img		img;
	char		*copy;
	float		*z_buffer;
	// TODO hold on this for now
	//! make init for these, then use them on draw_line
	// int			x_inc;	//! W * 4
	// int			y_inc;	//! H * 4
}				t_camera;

typedef struct s_ambient
{
	float		al_br;
	t_pixel		al_c;
}				t_ambient;

// al_br -> ambient light brightness
// al_c  -> ambient light color
typedef struct s_scene
{
	t_camera	cam;
	t_ambient   amb;
	t_light		*lights;
	t_figure	*figures;
}				t_scene;

typedef struct s_minirt
{
	t_xvar		*mlx;
	void		*win_rayt;
	void		*win_menu;
	t_menu		menu;
	t_scene		scene;
	float		stuff;
	bool		vscode;
}				t_minirt;

#endif