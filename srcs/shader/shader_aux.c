/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:58:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2024/12/13 14:05:33 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rgb_color(t_pixel *color, float surface_normal[3])
{
	color->r = 0.5 * ((surface_normal[0] + 1) * 256);
	color->g = 0.5 * ((surface_normal[1] + 1) * 256);
	color->b = 0.5 * ((surface_normal[2] + 1) * 256);
	color->rgb = color->r << 16 | color->g << 8 | color->b;
}
