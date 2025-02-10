/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/08 19:50:02 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

void	dup_image(t_minirt *s)
{
	ft_memmove(s->cam.copy, s->cam.img.data, (W + 32) * H * 4);
	return ;
}

void	restore_image(t_minirt *s, char *image)
{
	// ft_memmove(s->cam.img.data, s->cam.copy, (W + 32) * H * 4);
	ft_memmove(s->cam.img.data, image, (W + 32) * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	return ;
}

/* Split the image into Red, Green, Blue channels.
Create two copies of the image:
    Left Image: Retains only the red channel.
    Right Image: Retains only the green and blue channels (cyan). */
// void	separate(t_minirt *s)
// {
// 	unsigned int	*src;
// 	unsigned int	*left;
// 	unsigned int	*right;
// 	int				pixels;
// 	int				i;

// 	pixels = (W + 32) * H;
// 	src = (unsigned int *)s->cam.copy;
// 	left = (unsigned int *)s->cam.left;
// 	right = (unsigned int *)s->cam.right;
// 	i = 0;
// 	while (i < pixels)
// 	{
// 		left[i] = src[i] & 0xFFFF0000;
// 		right[i] = src[i] & 0xFF00FFFF;
// 		i++;
// 	}
// }

void	set_anaglyph(t_minirt *s)
{
	unsigned int	*src;
	unsigned int	*left;
	unsigned int	*right;
	int				pixels;
	int				i;

	pixels = (W + 32) * H;
	ft_bzero(s->cam.left, pixels);
	ft_bzero(s->cam.right, pixels);

	src = (unsigned int *)s->cam.copy;
	left = (unsigned int *)s->cam.left;
	right = (unsigned int *)s->cam.right;
	while (i < pixels)
	{
		unsigned int gray = (red * 299 + green * 587 + blue * 114) / 1000;
		// unsigned int alpha = src[i] & 0xFF000000;
		unsigned int red = (src[i] & 0x00FF0000) >> 16;
        unsigned int green = (src[i] & 0x0000FF00) >> 8;
        unsigned int blue = src[i] & 0x000000FF;

		// Left eye: red only
		left[i] = (gray << 16);
		// left[i] = alpha | (red << 16);

		// Right eye: convert to grayscale then apply as cyan
		right[i] = (gray << 8) | gray;
		// right[i] = alpha | (gray << 8) | gray;
		i++;
	}
}

void	set_right(t_minirt *s);

void	greyscale(t_minirt *s);


void separate(t_minirt *s)
{
    unsigned int *src = (unsigned int *)s->cam.copy;
    unsigned int *left = (unsigned int *)s->cam.left;
    unsigned int *right = (unsigned int *)s->cam.right;
    int pixels = (W + 32) * H;

    for (int i = 0; i < pixels; i++)
    {
        unsigned int alpha = src[i] & 0xFF000000;
        unsigned int red = (src[i] & 0x00FF0000) >> 16;
        unsigned int green = (src[i] & 0x0000FF00) >> 8;
        unsigned int blue = src[i] & 0x000000FF;

        // Left eye: red only
        left[i] = alpha | (red << 16);

        // Right eye: convert to grayscale then apply as cyan
        unsigned int gray = (red * 299 + green * 587 + blue * 114) / 1000;
        right[i] = alpha | (gray << 8) | gray;
    }
}

		// unsigned int alpha = src[i] & 0xFF000000;
		// unsigned int green = (src[i] & 0x00FF0000) >> 16;
		// unsigned int blue = (src[i] & 0x0000FF00) >> 8;
		// right[i] = alpha | (green << 8) | blue;


	// src = (unsigned int *)s->cam.copy;
	// left = (unsigned int *)s->cam.left;
	// right = (unsigned int *)s->cam.right;
	// i = 0;
	// while (i < pixels)
	// {
	// 	left[i] = src[i] & 0xFFFF0000;
	// 	right[i] = src[i] & 0xFF00FFFF;
	// 	i++;
	// }
