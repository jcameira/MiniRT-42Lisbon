/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/18 09:18:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


void	anti_aliasing_get_color(t_pixel *real_p)
{
	real_p->r /= RAYS_PER_PIXEL;
	real_p->g /= RAYS_PER_PIXEL;
	real_p->b /= RAYS_PER_PIXEL;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}
