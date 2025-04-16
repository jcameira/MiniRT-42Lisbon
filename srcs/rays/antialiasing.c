/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 15:36:55 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	anti_aliasing_get_color(t_pixel *real_p, int rays)
{
	real_p->r /= rays;
	real_p->g /= rays;
	real_p->b /= rays;
	real_p->rgb = real_p->r << 16 | real_p->g << 8 | real_p->b;
}
