/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/09 13:10:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	add_pixel_color(t_pixel *real_p, t_pixel to_add)
{
	real_p->r += to_add.r;
	real_p->g += to_add.g;
	real_p->b += to_add.b;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}

void	anti_aliasing_get_color(t_pixel *real_p)
{
	real_p->r /= 10;
	real_p->g /= 10;
	real_p->b /= 10;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}
