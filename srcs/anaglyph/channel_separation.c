/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel_separation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/10 17:50:20 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

/* Split the image into Red, Green, Blue channels.
Create two copies of the image:
    Left Image: Retains only the red channel.
    Right Image: Retains only the green and blue channels (cyan). */
void	create_left_right(t_minirt *s)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	cyan;
	// float	enhancedCyan;
	int	i;

	i = 0;
	dup_image(s->cam.red, s->cam.img.data);
	dup_image(s->cam.cyan, s->cam.img.data);
	// Process channel enhancement
	while (i < s->cam.pixels * 4)
	{
		red = s->cam.red[i + 1];
		green = s->cam.cyan[i + 2];
		blue = s->cam.cyan[i + 3];
		// // Optional: Apply non-linear enhancement to red channel
		// // This can help bring out more detail
		// float enhancedRed = powf(red / 255.0f, 0.7f) * 255.0f;
		// redImage->data[i] = (uint8_t)fminf(enhancedRed, 255.0f);
		// Desaturate green and blue channels
		s->cam.red[i + 2] = (uint8_t)(red * 0.3f);  // Green
		s->cam.red[i + 3] = (uint8_t)(red * 0.3f);  // BLue
		// Calculate cyan channel (average of green and blue with some weighting)
		cyan = (uint8_t)((green * 0.7f + blue * 0.7f) / 2.0f);
		// // Optional: Apply non-linear enhancement
		// enhancedCyan = powf(cyan / 255.0f, 0.7f) * 255.0f;
		// cyan = (uint8_t)fminf(enhancedCyan, 255.0f);
		// Zero out the red channel
		s->cam.cyan[i + 1] = 0;  // Red
		s->cam.cyan[i + 2] = cyan;  // Green
		s->cam.cyan[i + 3] = cyan;  // Blue
	}
}
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

/*
// Create a cyan-emphasized image for anaglyph processing
Image* createCyanImage(const Image* original) {
	if (!original || !original->data) {
		return NULL;
	}

	// Allocate memory for the cyan image
	Image* cyanImage = malloc(sizeof(Image));
	if (!cyanImage) {
		return NULL;
	}

	// Copy image metadata
	cyanImage->width = original->width;
	cyanImage->height = original->height;
	cyanImage->channels = original->channels;

	// Allocate pixel data
	size_t imageSize = original->width * original->height * original->channels;
	cyanImage->data = malloc(imageSize);
	if (!cyanImage->data) {
		free(cyanImage);
		return NULL;
	}

	// Copy original image data
	memcpy(cyanImage->data, original->data, imageSize);

	// Process cyan channel enhancement
	for (int i = 0; i < original->width * original->height * original->channels; i += original->channels) {
		// Combine green and blue channels for cyan effect
		uint8_t green = cyanImage->data[i + 1];
		uint8_t blue = cyanImage->data[i + 2];

		// Calculate cyan channel (average of green and blue with some weighting)
		uint8_t cyan = (uint8_t)((green * 0.7f + blue * 0.7f) / 2.0f);

		// Optional: Apply non-linear enhancement
		float enhancedCyan = powf(cyan / 255.0f, 0.7f) * 255.0f;
		cyan = (uint8_t)fminf(enhancedCyan, 255.0f);

		// Zero out the red channel
		cyanImage->data[i] = 0;  // Red
		cyanImage->data[i + 1] = cyan;  // Green
		cyanImage->data[i + 2] = cyan;  // Blue
	}

	return cyanImage;
}
*/
