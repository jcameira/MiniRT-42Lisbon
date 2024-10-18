/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:40:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/18 12:22:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_DEFINE_H

// or something like this
// output msgs
# define INVALID_RT	"RT file has wrong syntax"
# define FILE_NOT_FOUND	"file was not found"
# define NO_ARGS	"print how to use here"

// main miniRT
# define WINDOW_NAME	"miniRT"
# define MLX_ERROR 1
# define W 800
# define H 800


// struct here usually

typedef struct s_minirt
{
	t_xvar	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
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
