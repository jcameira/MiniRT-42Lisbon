/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_process.c.bak.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/02 20:59:56 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

// Apply horizontal shift to image pixels
void applyDepthShift(char *side, int shift, int dir)
{
	char	*temp;
	int		real_shift;
	int		source_x;
	int		dest_x;

	temp = ft_calloc((W + 32) * H * 4, 1);
	real_shift = shift * dir;

	// Process each row
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			// Calculate source position
			source_x = x;
			// Calculate destination position with shift
			dest_x = x + actualShift;
			// Check if destination is within image bounds
			if (dest_x >= 0 && dest_x < W) {
				// Calculate pixel indices
				int sourceIdx = (y * W + source_x) * 4;
				int destIdx = (y * W + dest_x) * 4;

				// Copy all channels for this pixel
				for (int c = 0; c < 4; c++) {
					temp[destIdx + c] = image->data[sourceIdx + c];
				}
			}
			// Note: if destX is out of bounds, those pixels remain black
			// in the temp buffer due to the initial memset
		}
	}

	// Handle edges based on shift direction
	if (real_shift > 0) {
		// Right shift: left edge needs filling
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < real_shift && x < W; x++) {
				int idx = (y * W + x) * 4;
				for (int c = 0; c < 4; c++) {
					temp[idx + c] = 0;  // Black edge
				}
			}
		}
	} else if (real_shift < 0) {
		// Left shift: right edge needs filling
		for (int y = 0; y < H; y++) {
			for (int x = W + real_shift; x < W; x++) {
				int idx = (y * W + x) * 4;
				for (int c = 0; c < 4; c++) {
					temp[idx + c] = 0;  // Black edge
				}
			}
		}
	}

	// Copy shifted data back to original image
	memcpy(image->data, temp, imageSize);
	// Clean up
	free(temp);
}

// merge red and cyan images
// t_camera *vp	struct with prt to all images in program
// int shift	value fpr depth effect
void	create_anaglyph(t_camera *vp, int shift)
{
	char		*shift_red;
	char		*shift_cyan;

	shift_red = ft_calloc((W + 32) * H * 4, 1);
	shift_cyan = ft_calloc((W + 32) * H * 4, 1);

	// Copy image data
	dup_image(shift_red, vp->red);
	dup_image(shift_cyan, vp->cyan);

	// Apply shifts
	applyDepthShift(shift_red, shift, -1);   // Shift red left
	applyDepthShift(shift_cyan, shift, 1);   // Shift cyan right

	// Merge the shifted images
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			int pixelIdx = (y * W + x) * 4;

			// Red channel from shifted red image
			anaglyphImage->data[pixelIdx] = shiftedRed->data[pixelIdx];

			// Green and blue channels from shifted cyan image
			anaglyphImage->data[pixelIdx + 1] = shiftedCyan->data[pixelIdx + 1];
			anaglyphImage->data[pixelIdx + 2] = shiftedCyan->data[pixelIdx + 2];
		}
	}

	// Clean up
	free(shift_red);
	free(shift_cyan);

	// return anaglyphImage;
}

// Complete pipeline example
void	not_create_anaglyph_main(t_minirt *s)
{
	t_camera	vp;
	int			shiftAmount;
	// char		*shift_red;
	// char		*shift_cyan;

	// shift_red = ft_calloc((W + 32) * H * 4, 1);
	// shift_cyan = ft_calloc((W + 32) * H * 4, 1);
	vp = s->cam;
	create_left_right(s);
	// Calculate shift amount (e.g., 2% of image width)
	shift = (int)(W * 0.02);
	// Create final anaglyph
	vp.anaglyph = createAnaglyph(vp, shift);
	// free(shift_red);
	// free(shift_cyan);
}


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

/*
// Example usage with edge feathering
void applyDepthShiftWithFeathering(
	Image* image,
	int shiftAmount,
	int shiftDirection
) {
	if (!image || !image->data) return;

	// Create temporary buffer
	size_t imageSize = image->width * image->height * image->channels;
	uint8_t* shiftedData = malloc(imageSize);
	if (!shiftedData) return;

	// Initialize buffer
	memset(shiftedData, 0, imageSize);

	int actualShift = shiftAmount * shiftDirection;

	// Process each row with feathering
	for (int y = 0; y < image->height; y++) {
		for (int x = 0; x < image->width; x++) {
			int sourceX = x;
			int destX = x + actualShift;

			if (destX >= 0 && destX < image->width) {
				int sourceIdx = (y * image->width + sourceX) * image->channels;
				int destIdx = (y * image->width + destX) * image->channels;

				// Calculate feathering factor for edges
				float feather = 1.0f;

				// Feather left edge
				if (destX < shiftAmount) {
					feather = (float)destX / shiftAmount;
				}
				// Feather right edge
				else if (destX > image->width - shiftAmount) {
					feather = (float)(image->width - destX) / shiftAmount;
				}

				// Apply feathered pixel copy
				for (int c = 0; c < image->channels; c++) {
					shiftedData[destIdx + c] = (uint8_t)(image->data[sourceIdx + c] * feather);
				}
			}
		}
	}

	// Copy result back to original image
	memcpy(image->data, shiftedData, imageSize);

	// Clean up
	free(shiftedData);
}
*/
