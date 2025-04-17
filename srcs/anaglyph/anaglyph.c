/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anaglyph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/16 23:53:14 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static unsigned int	set_pixel_value(t_pixel l, t_pixel r)
{
	t_pixel	out;

	out.r = (int)(dlm(0, 0) * l.r + dlm(0, 1) * l.g
			+ dlm(0, 2) * l.b + drm(0, 0) * r.r
			+ drm(0, 1) * r.g + drm(0, 2) * r.b);
	out.g = (int)(dlm(1, 0) * l.r + dlm(1, 1) * l.g
			+ dlm(1, 2) * l.b + drm(1, 0) * r.r
			+ drm(1, 1) * r.g + drm(1, 2) * r.b);
	out.b = (int)(dlm(2, 0) * l.r + dlm(2, 1) * l.g
			+ dlm(2, 2) * l.b + drm(2, 0) * r.r
			+ drm(2, 1) * r.g + drm(2, 2) * r.b);
	out.r = clamp(out.r, 0, 255);
	out.g = clamp(out.g, 0, 255);
	out.b = clamp(out.b, 0, 255);
	return ((out.r << 16) | (out.g << 8) | out.b);
}

static void	dubois(t_minirt *s, unsigned int *red_ptr, \
		unsigned int *cyan_ptr, unsigned int *anaglyph_ptr)
{
	int				i;
	t_pixel			l;
	t_pixel			r;

	i = -1;
	l = (t_pixel){0, 0, 0, 0};
	r = (t_pixel){0, 0, 0, 0};
	while (++i < s->scene.cam.pixels)
	{
		l.r = (cyan_ptr[i] & 0x00FF0000) >> 16;
		l.g = (cyan_ptr[i] & 0x0000FF00) >> 8;
		l.b = (cyan_ptr[i] & 0x000000FF);
		r.r = (red_ptr[i] & 0x00FF0000) >> 16;
		r.g = (red_ptr[i] & 0x0000FF00) >> 8;
		r.b = (red_ptr[i] & 0x000000FF);
		anaglyph_ptr[i] = set_pixel_value(l, r);
	}
}

void	create_anaglyph(t_minirt *s)
{
	unsigned int	*red_ptr;
	unsigned int	*cyan_ptr;
	unsigned int	*anaglyph_ptr;

	red_ptr = (unsigned int *)s->scene.cam.red;
	cyan_ptr = (unsigned int *)s->scene.cam.cyan;
	anaglyph_ptr = (unsigned int *)s->scene.cam.anaglyph;
	ft_printf("Anaglyph generation starting - Dubois algorithm\n");
	create_right_eye(s);
	create_left_eye(s);
	dubois(s, red_ptr, cyan_ptr, anaglyph_ptr);
	dup_image(s->scene.cam.img.data, s->scene.cam.anaglyph);
	ft_printf("Dubois finished - anaglyph created\n");
}
