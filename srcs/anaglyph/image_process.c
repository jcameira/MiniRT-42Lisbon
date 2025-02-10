/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/10 17:52:44 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

void	set_anaglyph(t_minirt *s)
{
	unsigned int	*src;
	unsigned int	*left;
	unsigned int	*right;
	int				pixels;
	int				i;

	pixels = (W + 32) * H;
	ft_bzero(s->cam.red, pixels);
	ft_bzero(s->cam.cyan, pixels);

	src = (unsigned int *)s->cam.copy;
	left = (unsigned int *)s->cam.red;
	right = (unsigned int *)s->cam.cyan;
	i = 0;
	while (i < pixels)
	{
		// unsigned int alpha = src[i] & 0xFF000000;
		unsigned int red = (src[i] & 0x00FF0000) >> 16;
        unsigned int green = (src[i] & 0x0000FF00) >> 8;
        unsigned int blue = src[i] & 0x000000FF;
		unsigned int gray = (red * 299 + green * 587 + blue * 114) / 1000;

		// Left eye: red only
		left[i] = (gray << 16);
		// red[i] = alpha | (red << 16);

		// Right eye: convert to grayscale then apply as cyan
		right[i] = (gray << 8) | gray;
		// cyan[i] = alpha | (gray << 8) | gray;
		i++;
	}
}

void	set_cyan(t_minirt *s);

void	greyscale(t_minirt *s);


void separate(t_minirt *s)
{
	unsigned int *src = (unsigned int *)s->cam.copy;
	unsigned int *left = (unsigned int *)s->cam.red;
	unsigned int *right = (unsigned int *)s->cam.cyan;
	int pixels = (W + 32) * H;

	for (int i = 0; i < pixels; i++)
	{
		unsigned int alpha = src[i] & 0xFF000000;
		unsigned int red = (src[i] & 0x00FF0000) >> 16;
		unsigned int green = (src[i] & 0x0000FF00) >> 8;
		unsigned int blue = src[i] & 0x000000FF;

		// Left eye: red only
		left[i] = alpha | (red << 16); // teste compare red

		// Right eye: convert to grayscale then apply as cyan
		unsigned int gray = (red * 299 + green * 587 + blue * 114) / 1000;
		// cyan[i] = alpha | (gray << 16); // teste
		right[i] = alpha | (gray << 8) | gray;
	}
}
