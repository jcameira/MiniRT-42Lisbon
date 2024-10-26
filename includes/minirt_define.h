/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/26 23:10:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

// or something like this
// output msgs
# define INVALID_RT	"RT file has wrong syntax"
# define FILE_NOT_FOUND	"file was not found"
# define NO_ARGS	"print how to use here"

// main miniRT
# define WINDOW_NAME "medium RT"
# define MLX_ERROR 1
# define W 800
# define H 800

// struct here usually
typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}				t_point;

typedef struct s_light
{
	float			o[3];
	struct s_light	*next;
	float			br;
	int				c;
}				t_light;

typedef struct s_sphere
{
	float	c[3];
	float	d;
}				t_sphere;

typedef struct s_plane
{
	float	p[3];
	float	nv[3];
}				t_plane;

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

typedef struct s_figure
{
	t_ftype			type;
	struct s_figure	*next;
	t_f				f;
	int				c;
}				t_figure;

typedef struct s_scene
{
	float		al_br;
	int			al_c;
	t_light		*lights;
	t_figure	*figures;
}				t_scene;

typedef struct s_camera
{
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
