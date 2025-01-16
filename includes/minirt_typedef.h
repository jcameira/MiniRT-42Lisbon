/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/14 20:27:59 by cjoao-de         ###   ########.fr       */
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
// struct here usually

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}	t_pixel;

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
	t_pixel	c;
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

typedef struct s_poly
{
	int	num_points;		// number of points in polygon (usually 3 or 4)
	int	vertex_list[4];	// the index number of vertices
	// int color;		// color of polygon
	// int shade;		// the final shade of color after lighting
	// int shading;		// type of lighting, flat or constant shading
	// int two_sided;	// flags if the polygon is two sided
	// int visible;		// used to remove backfaces
	// int active;		// used to turn faces on and off
	// int clipped;		// flags that polygon has been clipped or removed
	// float normal_length; // pre-computed magnitude of normal
}				t_poly;

typedef struct s_bbox
{
	int		id;				// identification number of object
	float	min[3];
	float	max[3];
	// ptr to object
	int		num_vertices;	// total number of vertices in object
	// point_3d	vertices_local[8];	// local vertices
	float	vertices_local[8][4];
	float	vertices_world[8][4];	// world vertices
	int		vertices_camera[8][4]; // camera vertices
	int		num_polys;		// the number of polygons in the object
	t_poly	polys[6]; // the polygons that make up the object
	// float radius;	// the average radius of object
	int		state;			// state of object
	float	world_pos[4];
	// point_3d	world_pos;	// position of object in world coordinates
}				t_bbox;

typedef union s_f
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
	t_quad		qu;
	t_bbox		ob;
	t_bbox		bb;
}				t_f;

typedef enum s_ltype
{
	L_SP,
	L_PL
}				t_ltype;

// SPhere, PLane, CYlinder, COne, QUad, OBject, BBox
typedef enum s_ftype
{
	SP,
	PL,
	CY,
	CO,
	QU,
	OB,
	BB
}				t_ftype;

// o  -> origin point
// br -> brightness
// c  -> color
typedef struct s_light
{
	t_ltype			type;
	struct s_light	*next;
	t_f				f;
	float			o[3];
	float			br;
	t_pixel			c;
}				t_light;

typedef enum s_ttype
{
	TEXTURE_SOLID,
	TEXTURE_CHECKER,
	TEXTURE_IMAGE
}				t_ttype;

typedef struct s_checker
{
	t_pixel	even;
	t_pixel	odd;
}				t_checker;

typedef struct s_texture
{
	t_ttype		type;
	union	u_tx
	{
		t_pixel		solid;
		t_checker	checker;
		t_img		image;
	}			tx;
}				t_texture;

// typedef struct s_material
// {
// 	t_texture		*texture; // Texture for the material
// }				t_material;

// f -> figure
// b -> bbox
// t -> texture
// c -> color
typedef struct s_figure
{
	t_ftype			type;
	struct s_figure	*next;
	t_f				f;
	t_bbox			b;
	// t_img			t;
	t_pixel			c;
	t_texture		texture;	// replaces t and c
}				t_figure;

// al_br -> ambient light brightness
// al_c  -> ambient light color
typedef struct s_scene
{
	int			has_al;
	float		al_br;
	t_pixel		al_c;
	t_light		*lights;
	t_figure	*figures;
}				t_scene;

// o -> origin
// dir -> direction
typedef struct s_ray
{
	float	o[3];
	float	dir[3];
}				t_ray;

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
	float		u;
	float		v;
	int			front_face;
	t_pixel		attenuation;
	t_texture	*texture;
	bool		light;
}				t_hitrecord;

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

// o   -> origin point
// nv  -> 3D normalized vector
// fov -> field of vision
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

typedef struct s_minirt
{
	t_xvar		*mlx;
	void		*win_rayt;
	void		*win_menu;
	t_camera	cam;
	t_menu		menu;
	t_scene		scene;
	float		stuff;
	bool		vscode;
}				t_minirt;

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

// w stand for normalization vector
typedef enum s_xyz
{
	x,
	y,
	z,
	w
}				t_xyz;

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

// typedef struct t_xpm_image
// {
// 	/
// };

#endif
