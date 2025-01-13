/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/13 15:09:49 by jcameira         ###   ########.fr       */
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
	real_p->r /= 500;
	real_p->g /= 500;
	real_p->b /= 500;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}
