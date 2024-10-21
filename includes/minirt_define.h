/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/21 03:32:02 by jcameira         ###   ########.fr       */
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
	t_point			o;
	float			br;
	int				c;
	struct s_light	*next;
}				t_light;

typedef struct s_sphere
{
	t_point	c;
	float	d;
}				t_sphere;

typedef struct s_plane
{
	t_point	p;
	t_point	nv;
}				t_plane;

typedef struct s_cylinder
{
	t_point	c;
	t_point	nv;
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
	t_point	o;
	t_point	nv;
	int		fov;
}				t_camera;
typedef struct s_minirt
{
	t_xvar	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	float	stuff;
}	t_minirt;

typedef struct s_pixel
{
	int		r;
	int		g;
	int		b;
	int		rgb;
	double	len;
	float	smooth;
}	t_pixel;

#endif
