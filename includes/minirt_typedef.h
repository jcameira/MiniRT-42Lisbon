/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:30:40 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/14 16:24:59 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPEDEF_H
# define MINIRT_TYPEDEF_H

typedef struct s_coord
{
	int		pos[2];
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

typedef enum s_material_type
{
	lambertian = 1,
	metal,
	dialetric,
	emission
}				t_material_type;

typedef enum s_texture_type
{
	solid_color = 1,
	checkered,
	image,
	bump_map
}				t_texture_type;

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
	t_img		img;
	bool		radio_one;
	bool		radio_two;
	bool		radio_three;
	bool		radio_four;
	t_pixel		color_picker;
	t_pixel		gradient_picker;
	char		**f_names;
	t_list		*objects;

}				t_menu;

typedef struct s_img_asset
{
	t_img		img;
	bool		sprite;
	u_int16_t	x_grid;
	u_int16_t	y_grid;
}				t_img_asset;

typedef struct s_img_assets
{
	t_img_asset	bt_clrpick;
	t_img_asset	bt_render;
	t_img_asset	label_figures;
	t_img_asset	label_materials;
	t_img_asset	bt_gradient;
}				t_img_assets;

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
	t_img		img;
	char		*copy;
	char		*red;
	char		*cyan;
	char		*anaglyph;
	int			pixels;
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
	float	nv[3];	//	Plane normal
	float	w[3];		//	w vector
	float	_d;
	// double D;		// Plane equation constant
}				t_quad;

typedef struct s_disk
{
	float	c[3];
	float	nv[3];
	float	r;
}				t_disk;

typedef struct s_cone
{
	float		c[3];
	float		nv[3];
	float		r;
	float		h;
	t_list		*bot_cap;
}				t_cone;

typedef struct s_object t_object;

// c  -> center point
// nv -> 3D normalized vector
// d  -> diameter
// h  -> height
typedef struct s_cylinder
{
	float		c[3];
	float		nv[3];
	float		r;
	float		h;
	t_list		*bot_cap;
	t_list		*top_cap;
}				t_cylinder;

// typedef union s_f
// {
// 	t_sphere	sp;
// 	t_plane		pl;
// 	t_cylinder	cy;
// 	t_quad		qu;
// }				t_f;

// SPhere, PLane, CYlinder, COne, QUad, OBject, BBox
typedef enum s_ftype
{
	SP,
	PL,
	CY,
	QU,
	DS,
	CO
}				t_ftype;

// al_br -> ambient light brightness
// al_c  -> ambient light color
typedef struct s_ambient
{
	int		has_al;
	float	al_br;
	t_pixel	al_c;
}				t_ambient;

typedef struct s_hitrecord t_hitrecord;

typedef void	(*t_obj_print)(t_list *obj);
typedef float	(*t_obj_inter)(t_list *obj, t_ray *ray, float min, float max);
typedef int		(*t_obj_normal)(t_list *obj, t_hitrecord *hit);
typedef t_ray	(*t_obj_scatter)(t_ray *in_r, t_hitrecord *hit);
typedef t_pixel	(*t_obj_color)(t_list *obj, t_hitrecord *hit);

typedef struct s_texture
{
	t_texture_type	type;
	t_pixel			checkered_c;
	float			scale;
	char			*texture_file;
	t_img			texture;
}				t_texture;

typedef struct s_material
{
	t_material_type	type;
	t_texture		tex;
	t_pixel			c;
	t_obj_scatter	scatter;
	t_obj_color		get_color;
	float			br;
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
	float		tg[3];
	float		bitg[3];
	float		t;
	int			front_face;
	t_list		*object;
	float		u;
	float		v;
	t_material	mat;
	t_pixel		attenuation;
}				t_hitrecord;

typedef struct s_object
{
	t_ftype			type;
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
		t_disk		ds;
		t_cone		co;
	};
}				t_object;

// o  -> origin point
// br -> brightness
// c  -> color
typedef struct s_light
{
	t_object		*obj;
	t_obj_print		print;
	t_pixel			c;
}				t_light;

typedef struct s_scene
{
	t_viewport	vp;
	t_camera	cam;
	t_ambient	amb;
	float		quality;
	int			quality_idx;
	t_list		*lights;
	t_list		*objects;
	bool		loop;
	u_int16_t	loop_ctr;
}				t_scene;

typedef struct s_minirt
{
	t_xvar			*mlx;
	void			*win_rayt;
	void			*win_menu;
	t_img_assets	assets;
	t_menu			menu;
	t_scene			scene;
	float			stuff;
	bool			render;
	bool			vscode;
}					t_minirt;

#endif
