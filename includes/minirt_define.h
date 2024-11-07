/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/11/06 15:05:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// or something like this
// output msgs
# define INVALID_RT	"Invalid file type\n"
# define FILE_NOT_FOUND	"%s: Error opening file\n"
# define UNKNOWN_ELEMENT "%s: Unknown element detected\n"
# define NO_AMBIENCE "%s: No ambience light in file\n"
# define NO_CAMERA "%s: No camera in file\n"
# define NO_LIGHT "%s: No light in file\n"
# define FOV_ERROR "Camera fov out of range\n"
# define POINT_ERROR "Point/Vector incorrectly composed in file\n"
# define COLOR_ERROR "Color incorrectly composed in file\n"
# define AMBIENCE_USAGE "Usage: A brithness[0.0,1.0] \
r[0,255],g[0,255],b[0,255]\n"
# define CAMERA_USAGE "Usage: C x,y,z x[-1,1],y[-1,1],z[-1,1] \
fov[0.180]\n"
# define LIGHT_USAGE "Usage: L x,y,z brithness[0.0,1.0] \
r[0,255],g[0,255],b[0,255]\n"
# define SPHERE_USAGE "Usage: sp x,y,z diameter \
r[0,255],g[0,255],b[0,255]\n"
# define PLANE_USAGE "Usage: pl x,y,z x[-1,1],y[-1,1],z[-1,1] \
r[0,255],g[0,255],b[0,255]\n"
# define CYLINDER_USAGE "Usage: cy x,y,z x[-1,1],y[-1,1],z[-1,1] \
diameter height r[0,255],g[0,255],b[0,255]\n"
# define MULTIPLE_AMBIENCE "Multiple ambience light elements\n"
# define MULTIPLE_CAMERAS "Multiple camera elements\n"
# define NO_ARGS "Usage: myprog file\n"
# define NO_SPACE "No more space left in device\n"

// main miniRT
# define WINDOW_NAME "medium RT"
# define MLX_ERROR 1
# define W 320
# define H 200

//Limits
# define FOV_MIN 0
# define FOV_MAX 180
# define BR_MIN 0
# define BR_MAX 1
# define RGB_MIN 0
# define RGB_MAX 255
# define NV_AXIS_MIN -1
# define NV_AXIS_MAX 1

// struct here usually
// o  -> origin point
// br -> brightness
// c  -> color
typedef struct s_light
{
	float			o[3];
	struct s_light	*next;
	float			br;
	int				c;
}				t_light;

// c -> center point
// d -> diameter
typedef struct s_sphere
{
	float	c[3];
	float	d;
}				t_sphere;

// p  -> point
// nv -> 3D normalized vector
typedef struct s_plane
{
	float	p[3];
	float	nv[3];
}				t_plane;

// c  -> center point
// nv -> 3D normalized vector
// d  -> diameter
// d  -> height
typedef struct s_cylinder
{
	float	c[3];
	float	nv[3];
	float	d;
	float	h;
}				t_cylinder;

typedef union s_f
{
	t_sphere	sp;
	t_plane		pl;
	t_cylinder	cy;
}				t_f;

typedef enum s_ftype
{
	SP,
	PL,
	CY
}				t_ftype;

// f -> figure
// c -> color
typedef struct s_figure
{
	t_ftype			type;
	struct s_figure	*next;
	t_f				f;
	int				c;
}				t_figure;

// al_br -> ambient light brightness
// al_c  -> ambient light color
typedef struct s_scene
{
	int			has_al;
	float		al_br;
	int			al_c;
	t_light		*lights;
	t_figure	*figures;
}				t_scene;

// o   -> origin point
// nv  -> 3D normalized vector
// fov -> field of vision
typedef struct s_camera
{
	int		has_cam;
	float	o[3];
	float	nv[3];
	int		fov;
	t_img	img;
}				t_camera;

typedef struct s_minirt
{
	t_xvar		*mlx_ptr;
	void		*win_ptr;
	t_camera	cam;
	t_scene		scene;
	float		stuff;
	// added
	char		*argv1;
}	t_minirt;

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
}	t_pixel;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef enum s_xyz
{
	x,
	y,
	z
}	t_xyz;

#endif
