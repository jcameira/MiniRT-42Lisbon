/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anaglyph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 13:51:37 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// create_left_right
// Converts to BW, for full color replace:`
// pixel.rgb = (pixel.r * 299 + pixel.g * 587 + pixel.b * 114) / 1000;
// cyan[i] = (pixel.rgb << 8) | pixel.rgb;
// with:
// cyan[i] = (pixel.g << 8) | pixel.b;

/* Split the image into Red, Green, Blue channels.
Create two copies of the image:
Left Image: Retains only the red channel.
Right Image: Retains only the green and blue channels (cyan). */
static void	create_left_right(t_camera cam)
{
	t_pixel	pixel;
	unsigned int *src;
	unsigned int *red;
	unsigned int *cyan;
	int	i;

	src = (unsigned int *)cam.copy;
	red = (unsigned int *)cam.red;
	cyan = (unsigned int *)cam.cyan;
	i = -1;
	while (++i < cam.pixels)
	{
		pixel.r = (src[i] & 0x00FF0000) >> 16;
		pixel.g = (src[i] & 0x0000FF00) >> 8;
		pixel.b = src[i] & 0x000000FF;
		red[i] = pixel.r << 16;
		pixel.rgb = (pixel.r * 299 + pixel.g * 587 + pixel.b * 114) / 1000;
		cyan[i] = (pixel.rgb << 8) | pixel.rgb;
	}
}

// Apply horizontal shift to image pixels
static void apply_depth_shift(t_camera cam, char *buffer, int shift, int dir)
{
	int		dest_x;
	int		x;
	int		y;
	char	*tmp;

	tmp = ft_calloc(cam.pixels * 4, 1);
	if (!tmp)
		return;
	shift *= dir;
	y = -1;
	while (y++ < H) {
		x = 0;
		while (x < W) {
			dest_x = x + shift;
			if (dest_x >= 0 && dest_x < W)
			{
				*(unsigned int *)(tmp + (y * cam.img.size_line + dest_x * 4)) = \
					*(unsigned int *)(buffer + (y * cam.img.size_line + x * 4));
			}
			x++;
		}
	}
	ft_memmove(buffer, tmp, cam.pixels * 4);
	free(tmp);
}

// Complete anaglyph creation workflow
void create_anaglyph(t_minirt *s)
{
	int				shift;
	int				i;
	unsigned int	*red_ptr;
	unsigned int	*cyan_ptr;
	unsigned int	*anaglyph_ptr;

	shift = (int)(W * 0.02);
	if (!s->scene.cam.copy || !s->scene.cam.red || !s->scene.cam.cyan || !s->scene.cam.anaglyph)
	{
		if (!s->scene.cam.red || !s->scene.cam.cyan || !s->scene.cam.anaglyph)
			return ;
		if (!s->scene.cam.anaglyph)
			s->scene.cam.anaglyph = malloc(s->scene.cam.pixels * 4);
	}
	create_left_right(s->scene.cam);
	apply_depth_shift(s->scene.cam, s->scene.cam.red, shift, -1);
	apply_depth_shift(s->scene.cam, s->scene.cam.cyan, shift, 1);
	red_ptr = (unsigned int *)s->scene.cam.red;
	cyan_ptr = (unsigned int *)s->scene.cam.cyan;
	anaglyph_ptr = (unsigned int *)s->scene.cam.anaglyph;
	i = -1;
	while (i++ < s->scene.cam.pixels)
		anaglyph_ptr[i] = (red_ptr[i] & 0x00FF0000) | (cyan_ptr[i] & 0xFF00FFFF);
	dup_image(s->scene.cam.img.data, s->scene.cam.anaglyph);
}
