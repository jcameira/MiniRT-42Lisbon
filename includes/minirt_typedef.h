/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/27 05:32:02 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPEDEF_H
# define MINIRT_TYPEDEF_H

typedef float	vec3[3];
typedef int		coord[2];

typedef struct s_vec3
{
	vec3	vec;
}				t_vec3;

typedef struct s_coord
{
	coord	pos;
}				t_coord;

typedef enum s_interval
{
	min,
	max
}				t_interval;

typedef enum s_xyz
{
	x,
	y,
	z,
	w
}				t_xyz;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}				t_rect;

typedef struct s_circle
{
	int	x_center;
	int	y_center;
	int	radius;
	int	color;
}				t_circle;

typedef struct t_line
{
	int			origin[2];
	int			dest[2];
	int			dx;
	int			dy;
	int			x_inc;
	int			y_inc;
	int			error;
	char		*pix;
	int			color;
}				t_line;

// o -> origin
// dir -> direction
typedef struct s_ray
{
	float	o[3];
	float	dir[3];
}				t_ray;

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}				t_pixel;

typedef struct s_menu
{
	t_img	img;
	t_img	asset1;
	t_img	bt_render;
	bool	radio_one;
	int		background;
	t_pixel	color_picker;
	bool	click_spam;
}				t_menu;

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
	//t_viewport	vp;
	t_img		img;
	char		*copy;
	float		*z_buffer;
	// TODO hold on this for now
	//! make init for these, then use them on draw_line
	// int			x_inc;	//! W * 4
	// int			y_inc;	//! H * 4
}				t_camera;

// fl -> focal length
// v_height -> viewport height
// vh -> horizontal viewport vector
// deltah -> horizontal distance between pixels
// v_width -> viewport width
// vv -> vertical viewport vector
// deltav -> vertical distance between pixels
// vul -> viewport upper left corner
// pixel00l -> pixel (0,0) center location
typedef struct s_viewport
{
	int		fl;
	float	v_height;
	float	v_width;
	float	vh[3];
	float	deltah[3];
	float	vv[3];
	float	deltav[3];
	float	vul[3];
	float	pixel00l[3];
}				t_viewport;

// c -> center point
// d -> diameter
typedef struct s_sphere
{
	float	c[3];
	float	r;
}				t_sphere;

// p  -> point
// nv -> 3D normalized vector

typedef struct s_plane
{
	float	p[3];
	float	nv[3];
}				t_plane;

//? capital Q and D changed to _q, _d because norminette bitching
typedef struct t_quad
{
	float	_q[3];		// Starting corner of the quad
	float	u[3];
	float	v[3];		// Edge vectors
	float	normal[3];	//	Plane normal
	float	w[3];		//	w vector
	float	_d;
	// double D;		// Plane equation constant
}				t_quad;

// c  -> center point
// nv -> 3D normalized vector
// d  -> diameter
// h  -> height
typedef struct s_cylinder
{
	float	c[3];
	float	nv[3];
	float	r;
	float	h;
}				t_cylinder;

typedef union s_f
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_quad		qu;
}				t_f;

// al_br -> ambient light brightness
// al_c  -> ambient light color
typedef struct s_ambient
{
	int			has_al;
	float		al_br;
	t_pixel		al_c;
}				t_ambient;

typedef struct s_hitrecord	t_hitrecord;

typedef void	(*t_obj_print)(t_list *obj);
typedef float	(*t_obj_inter)(t_list *obj, t_ray *ray, float min, float max);
typedef void	(*t_obj_normal)(t_list *obj, t_hitrecord *hit);
typedef t_ray	(*t_obj_scatter)(t_ray *in_r, t_hitrecord *hit);

typedef struct s_material
{
	t_pixel			c;
	int				type;
	t_obj_scatter	scatter;
	float			fuzz;
	float			ri;
}				t_material;

// p -> hit point
// normal -> surface normal
// t -> distance between ray origin and hit point
// front_face -> bool to see if the hit point is inside or outside of the object
// attenuation -> color attenuation for bouncing rays
typedef struct s_hitrecord
{
	float		p[3];
	float		normal[3];
	float		t;
	int			front_face;
	t_list		*object;
	//float		u;
	//float		v;
	t_material	mat;
	t_pixel		attenuation;
	//bool		light;
}				t_hitrecord;

// o  -> origin point
// br -> brightness
// c  -> color
typedef struct s_light
{
	t_f				f;
	t_obj_print		print;
	t_pixel			c;
	float			br;
}				t_light;

typedef struct s_object
{
	t_material		mat;
	t_obj_print		print;
	t_obj_inter		hit;
	t_obj_normal	normal;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
		t_quad		qu;
	};
}				t_object;

typedef struct s_scene
{
	t_viewport	vp;
	t_camera	cam;
	t_ambient	amb;
	t_list		*lights;
	t_list		*objects;
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