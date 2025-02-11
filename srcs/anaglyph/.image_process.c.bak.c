/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .image_process.c.bak.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/11 19:42:22 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

// Apply horizontal shift to image pixels
void applyDepthShift(
	Image* image,          // Image to be shifted
	int shiftAmount,       // Number of pixels to shift
	int shiftDirection     // -1 for left, 1 for right
) {
	if (!image || !image->data) return;

	// Create temporary buffer for shifted image
	size_t imageSize = image->width * image->height * image->channels;
	uint8_t* shiftedData = malloc(imageSize);
	if (!shiftedData) return;

	// Initialize buffer to black
	memset(shiftedData, 0, imageSize);

	// Calculate actual shift
	int actualShift = shiftAmount * shiftDirection;

	// Process each row
	for (int y = 0; y < image->height; y++) {
		for (int x = 0; x < image->width; x++) {
			// Calculate source position
			int sourceX = x;

			// Calculate destination position with shift
			int destX = x + actualShift;

			// Check if destination is within image bounds
			if (destX >= 0 && destX < image->width) {
				// Calculate pixel indices
				int sourceIdx = (y * image->width + sourceX) * image->channels;
				int destIdx = (y * image->width + destX) * image->channels;

				// Copy all channels for this pixel
				for (int c = 0; c < image->channels; c++) {
					shiftedData[destIdx + c] = image->data[sourceIdx + c];
				}
			}
			// Note: if destX is out of bounds, those pixels remain black
			// in the shiftedData buffer due to the initial memset
		}
	}

	// Handle edges based on shift direction
	if (actualShift > 0) {
		// Right shift: left edge needs filling
		for (int y = 0; y < image->height; y++) {
			for (int x = 0; x < actualShift && x < image->width; x++) {
				int idx = (y * image->width + x) * image->channels;
				for (int c = 0; c < image->channels; c++) {
					shiftedData[idx + c] = 0;  // Black edge
				}
			}
		}
	} else if (actualShift < 0) {
		// Left shift: right edge needs filling
		for (int y = 0; y < image->height; y++) {
			for (int x = image->width + actualShift; x < image->width; x++) {
				int idx = (y * image->width + x) * image->channels;
				for (int c = 0; c < image->channels; c++) {
					shiftedData[idx + c] = 0;  // Black edge
				}
			}
		}
	}

	// Copy shifted data back to original image
	memcpy(image->data, shiftedData, imageSize);

	// Clean up
	free(shiftedData);
}

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

// Example usage
int not_applyDepthShift_main() {
	// Load test image
	Image* testImage = loadImage("test.jpg");
	if (!testImage) return 1;

	// Basic shift
	printf("Applying basic shift...\n");
	applyDepthShift(testImage, 20, 1);  // Shift right by 20 pixels
	saveImage(testImage, "shifted.png");

	// Load another test image
	Image* testImage2 = loadImage("test.jpg");
	if (!testImage2) return 1;

	// Shift with feathering
	printf("Applying shift with feathering...\n");
	applyDepthShiftWithFeathering(testImage2, 20, 1);
	saveImage(testImage2, "shifted_feathered.png");

	// Clean up
	freeImage(testImage);
	freeImage(testImage2);

	return 0;
}

// Create final anaglyph by merging pure red and cyan images
void	create_anaglyph(
	const Image* redImage,     // Pure red channel image (shifted left)
	const Image* cyanImage,    // Pure cyan image (shifted right)
	int shiftAmount           // Pixel shift for stereo effect
)
{
	// Create shifted copies of red and cyan images
	Image* shiftedRed = malloc(sizeof(Image));
	Image* shiftedCyan = malloc(sizeof(Image));

	shiftedRed->width = redImage->width;
	shiftedRed->height = redImage->height;
	shiftedRed->channels = redImage->channels;
	shiftedRed->data = malloc(imageSize);

	shiftedCyan->width = cyanImage->width;
	shiftedCyan->height = cyanImage->height;
	shiftedCyan->channels = cyanImage->channels;
	shiftedCyan->data = malloc(imageSize);

	// Copy image data
	memcpy(shiftedRed->data, redImage->data, imageSize);
	memcpy(shiftedCyan->data, cyanImage->data, imageSize);

	// Apply shifts
	applyDepthShift(shiftedRed, shiftAmount, -1);   // Shift red left
	applyDepthShift(shiftedCyan, shiftAmount, 1);   // Shift cyan right

	// Merge the shifted images
	for (int y = 0; y < anaglyphImage->height; y++) {
		for (int x = 0; x < anaglyphImage->width; x++) {
			int pixelIdx = (y * anaglyphImage->width + x) * anaglyphImage->channels;

			// Red channel from shifted red image
			anaglyphImage->data[pixelIdx] = shiftedRed->data[pixelIdx];

			// Green and blue channels from shifted cyan image
			anaglyphImage->data[pixelIdx + 1] = shiftedCyan->data[pixelIdx + 1];
			anaglyphImage->data[pixelIdx + 2] = shiftedCyan->data[pixelIdx + 2];
		}
	}

	// Clean up
	free(shiftedRed->data);
	free(shiftedCyan->data);
	free(shiftedRed);
	free(shiftedCyan);

	return anaglyphImage;
}

// Complete pipeline example
int not_create_anaglyph_main() {
	// Load original image
	Image* originalImage = loadImage("input.jpg");
	if (!originalImage) {
		printf("Failed to load input image\n");
		return 1;
	}

	// Create pure red and cyan images
	Image* redImage = createRedImage(originalImage);
	Image* cyanImage = createCyanImage(originalImage);

	// Calculate shift amount (e.g., 2% of image width)
	int shiftAmount = (int)(originalImage->width * 0.02);

	// Create final anaglyph
	Image* anaglyphResult = createAnaglyph(redImage, cyanImage, shiftAmount);

	// Save output
	saveImage(anaglyphResult, "anaglyph_output.png");

	// Optional: Save intermediate results for verification
	saveImage(redImage, "red_channel.png");
	saveImage(cyanImage, "cyan_channel.png");

	// Clean up
	freeImage(originalImage);
	freeImage(redImage);
	freeImage(cyanImage);
	freeImage(anaglyphResult);

	return 0;
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
