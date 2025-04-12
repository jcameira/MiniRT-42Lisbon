/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:24:22 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 15:32:57 by cjoao-de         ###   ########.fr       */
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
