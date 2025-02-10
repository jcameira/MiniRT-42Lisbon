/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/10 22:44:24 by cjoao-de         ###   ########.fr       */
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

	src = (unsigned int *)s->cam.copy;
	red = (unsigned int *)s->cam.red;
	cyan = (unsigned int *)s->cam.cyan;
	i = -1;
	while (i++ < s->cam.pixels)
	{
		pixel.r = (src[i] & 0x00FF0000) >> 16;
		pixel.g = (src[i] & 0x0000FF00) >> 8;
		pixel.b = src[i] & 0x000000FF;
		red[i] = pixel.r << 16;
		pixel.rgb = (pixel.r * 299 + pixel.g * 587 + pixel.b * 114) / 1000;
		cyan[i] = (pixel.rgb << 8) | pixel.rgb;
	}
}

/* copy before culling
void	create_left_right(t_minirt *s)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	unsigned int gray;
	unsigned int *src = (unsigned int *)s->cam.copy;
	unsigned int *red = (unsigned int *)s->cam.red;
	unsigned int *cyan = (unsigned int *)s->cam.cyan;
	// float	enhancedCyan;
	// uint8_t	cyan;
	int	i;

	i = -1;
	// Process channel enhancement
	while (i++ < s->cam.pixels)
	{
		r = (src[i] & 0x00FF0000) >> 16;
		g = (src[i] & 0x0000FF00) >> 8;
		b = src[i] & 0x000000FF;
		red[i] = ((src[i] & 0x00FF0000) >> 16) << 16;  // Green

		// // Optional: Apply non-linear enhancement to red channel
		// // This can help bring out more detail
		// float enhancedRed = powf(red / 255.0f, 0.7f) * 255.0f;
		// redImage->data[i] = (uint8_t)fminf(enhancedRed, 255.0f);
		// Desaturate green and blue channels
		// s->cam.red[i + 2] = (uint8_t)(red * 0.3f);  // Green
		// s->cam.red[i + 3] = (uint8_t)(red * 0.3f);  // BLue

		// Calculate cyan channel (average of green and blue with some weighting)
		// uint8_t cy = (uint8_t)((g * 0.7f + b * 0.7f) / 2.0f);
		// cyan[i] = (cy << 8) | cy;
		// Optional: Apply non-linear enhancement
		// enhancedCyan = powf(cyan / 255.0f, 0.7f) * 255.0f;
		// cyan = (uint8_t)fminf(enhancedCyan, 255.0f);
		unsigned int gray = (r * 299 + g * 587 + b * 114) / 1000;
		cyan[i] = (gray << 8) | gray;
	}
}
*/
/* copy before norminette
void	create_left_right(t_minirt *s)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	cyan;
	// float	enhancedCyan;
	int	i;

	dup_image(s->cam.red, s->cam.img.data);
	dup_image(s->cam.cyan, s->cam.img.data);
	// Process channel enhancement
	// for (int i = 0;
	// 	i < original->width * original->height * original->channels;
	// 	i += original->channels)
	i = 0;
	while (i < s->cam.pixels * 4)
	{
		// Emphasize red channel
		red = s->cam.red[i + 1];
		green = s->cam.cyan[i + 2];
		blue = s->cam.cyan[i + 3];
		// red = redImage->data[i];
		// green = cyanImage->data[i + 1];
		// blue = cyanImage->data[i + 2];

		// // Optional: Apply non-linear enhancement to red channel
		// // This can help bring out more detail
		// float enhancedRed = powf(red / 255.0f, 0.7f) * 255.0f;
		// redImage->data[i] = (uint8_t)fminf(enhancedRed, 255.0f);

		// Desaturate green and blue channels
		s->cam.red[i + 2] = (uint8_t)(red * 0.3f);  // Green
		s->cam.red[i + 3] = (uint8_t)(red * 0.3f);  // BLue
		// redImage->data[i + 1] = (uint8_t)(red * 0.3f);  // Green
		// redImage->data[i + 2] = (uint8_t)(red * 0.3f);  // Blue

		// Calculate cyan channel (average of green and blue with some weighting)
		cyan = (uint8_t)((green * 0.7f + blue * 0.7f) / 2.0f);

		// // Optional: Apply non-linear enhancement
		// enhancedCyan = powf(cyan / 255.0f, 0.7f) * 255.0f;
		// cyan = (uint8_t)fminf(enhancedCyan, 255.0f);

		// Zero out the red channel
		s->cam.cyan[i + 1] = 0;  // Red
		s->cam.cyan[i + 2] = cyan;  // Green
		s->cam.cyan[i + 3] = cyan;  // Blue
		// cyanImage->data[i] = 0;  // Red
		// cyanImage->data[i + 1] = cyan;  // Green
		// cyanImage->data[i + 2] = cyan;  // Blue
	}
	// return redImage;
}
	*/
