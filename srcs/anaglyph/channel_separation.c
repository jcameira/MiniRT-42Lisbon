/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/02 21:38:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

/* Split the image into Red, Green, Blue channels.
Create two copies of the image:
	Left Image: Retains only the red channel.
	Right Image: Retains only the green and blue channels (cyan). */
void	create_left_right(t_minirt *s)
{
	t_pixel	pixel;
	unsigned int *src;
	unsigned int *red;
	unsigned int *cyan;
	int	i;

	src = (unsigned int *)s->scene.cam.copy;
	red = (unsigned int *)s->scene.cam.red;
	cyan = (unsigned int *)s->scene.cam.cyan;
	i = -1;
	while (i++ < s->scene.cam.pixels)
	{
		pixel.r = (src[i] & 0x00FF0000) >> 16;
		pixel.g = (src[i] & 0x0000FF00) >> 8;
		pixel.b = src[i] & 0x000000FF;
		red[i] = pixel.r << 16;
		pixel.rgb = (pixel.r * 299 + pixel.g * 587 + pixel.b * 114) / 1000;
		cyan[i] = (pixel.rgb << 8) | pixel.rgb;
	}
}
