/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 01:01:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/03 02:25:26 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	clean(char *image)
{
	unsigned int *pixels = (unsigned int *)image;
	int similar_threshold = 30;  // Threshold for color similarity
	int stride = W + 32;  // Define stride explicitly for clarity

	// Loop through each pixel in image
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			int idx = y * (W + 32) + x;
			unsigned int pixel = pixels[idx];

			// Check if pixel is black (RGB = 0,0,0)
			if ((pixel & 0x00FFFFFF) == 0) {
				unsigned int neighbors[4];  // To store diagonal neighbors
				int neighbor_count = 0;
				// int nonblack_count = 0;  // Count non-black neighbors

				// Collect diagonal neighbors
				// Top-left
				if (y > 0 && x > 0 && (pixels[(y-1) * stride + (x-1)] & 0x00FFFFFF) != 0)
				{
					unsigned int neighbor = pixels[(y-1) * stride + (x-1)];
					neighbors[neighbor_count++] = neighbor;
					// if ((neighbor & 0x00FFFFFF) != 0) nonblack_count++;
				}

				// Top-right
				if (y > 0 && x < W-1  && (pixels[(y-1) * stride + (x+1)] & 0x00FFFFFF) != 0)
				{
					unsigned int neighbor = pixels[(y-1) * stride + (x+1)];
					neighbors[neighbor_count++] = neighbor;
					// if ((neighbor & 0x00FFFFFF) != 0) nonblack_count++;
				}

				// Bottom-left
				if (y < H-1 && x > 0  && (pixels[(y+1) * stride + (x-1)] & 0x00FFFFFF) != 0) {
					unsigned int neighbor = pixels[(y+1) * stride + (x-1)];
					neighbors[neighbor_count++] = neighbor;
					// if ((neighbor & 0x00FFFFFF) != 0) nonblack_count++;
				}

				// Bottom-right
				if (y < H-1 && x < W-1  && (pixels[(y+1) * stride + (x+1)] & 0x00FFFFFF) != 0) {
					unsigned int neighbor = pixels[(y+1) * stride + (x+1)];
					neighbors[neighbor_count++] = neighbor;
					// if ((neighbor & 0x00FFFFFF) != 0) nonblack_count++;
				}

				// Need at least 3 neighbors to proceed
				// if (neighbor_count >= 3 && nonblack_count >= 3) {
				if (neighbor_count >= 3) {
					int similar_pairs = 0;

					// Compare each pair of neighbors
					for (int i = 0; i < neighbor_count - 1; i++) {
						// Skip black pixels
						// if ((neighbors[i] & 0x00FFFFFF) == 0)
						// 	continue;
						for (int j = i + 1; j < neighbor_count; j++) {
							// // Skip black pixels
							// if ((neighbors[j] & 0x00FFFFFF) == 0)
							// 	continue;

							unsigned int r1 = (neighbors[i] & 0x00FF0000) >> 16;
							unsigned int g1 = (neighbors[i] & 0x0000FF00) >> 8;
							unsigned int b1 = (neighbors[i] & 0x000000FF);

							unsigned int r2 = (neighbors[j] & 0x00FF0000) >> 16;
							unsigned int g2 = (neighbors[j] & 0x0000FF00) >> 8;
							unsigned int b2 = (neighbors[j] & 0x000000FF);

							// Check if colors are similar
							if (abs((int)r1 - (int)r2) <= similar_threshold &&
								abs((int)g1 - (int)g2) <= similar_threshold &&
								abs((int)b1 - (int)b2) <= similar_threshold) {
								similar_pairs++;
							}
						}
					}

					// If we have enough similar pairs (for 3 neighbors we need 3 pairs)
					if (similar_pairs >= 3) {
						unsigned int avg_r = 0, avg_g = 0, avg_b = 0;
						// int valid_pixels = 0;

						// Calculate average of non-black neighbors only
						for (int i = 0; i < neighbor_count; i++)
						{
							avg_r += (neighbors[i] & 0x00FF0000) >> 16;
							avg_g += (neighbors[i] & 0x0000FF00) >> 8;
							avg_b += (neighbors[i] & 0x000000FF);
							// Skip black pixels in average calculation
							// if ((neighbors[i] & 0x00FFFFFF) != 0) {
							// 	avg_r += (neighbors[i] & 0x00FF0000) >> 16;
							// 	avg_g += (neighbors[i] & 0x0000FF00) >> 8;
							// 	avg_b += (neighbors[i] & 0x000000FF);
							// 	valid_pixels++;
							// }
						}
						avg_r /= neighbor_count;
						avg_g /= neighbor_count;
						avg_b /= neighbor_count;
						unsigned int alpha = pixel & 0xFF000000;
						pixels[idx] = alpha | (avg_r << 16) | (avg_g << 8) | avg_b;

						// Only average if we have valid pixels
						// if (valid_pixels > 0) {
						// 	avg_r /= valid_pixels;
						// 	avg_g /= valid_pixels;
						// 	avg_b /= valid_pixels;

						// 	// Replace black pixel with average color, preserving alpha
						// 	unsigned int alpha = pixel & 0xFF000000;
						// 	pixels[idx] = alpha | (avg_r << 16) | (avg_g << 8) | avg_b;
						// }
					}
				}
			}
		}
	}
}



// DEEPSEEK

// Helper function to check if two colors are "near" the same
int is_near_same_color(uint32_t color1, uint32_t color2, int threshold) {
	int a1 = (color1 >> 24) & 0xFF;
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int a2 = (color2 >> 24) & 0xFF;
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	int diff_a = abs(a1 - a2);
	int diff_r = abs(r1 - r2);
	int diff_g = abs(g1 - g2);
	int diff_b = abs(b1 - b2);

	return (diff_a <= threshold && diff_r <= threshold && diff_g <= threshold && diff_b <= threshold);
}

// Helper function to calculate the average of a set of colors
uint32_t average_color(uint32_t *colors, int count) {
	uint32_t a_sum = 0, r_sum = 0, g_sum = 0, b_sum = 0;

	for (int i = 0; i < count; i++) {
		a_sum += (colors[i] >> 24) & 0xFF;
		r_sum += (colors[i] >> 16) & 0xFF;
		g_sum += (colors[i] >> 8) & 0xFF;
		b_sum += colors[i] & 0xFF;
	}

	uint32_t a_avg = a_sum / count;
	uint32_t r_avg = r_sum / count;
	uint32_t g_avg = g_sum / count;
	uint32_t b_avg = b_sum / count;

	return (a_avg << 24) | (r_avg << 16) | (g_avg << 8) | b_avg;
}

// Main clean function
void clean2(uint32_t *image, int width, int height, int threshold) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			uint32_t *pixel = &image[y * width + x];

			// Check if the pixel is black
			if (*pixel == 0xFF000000) { // ARGB black pixel
				uint32_t diagonal_colors[4];
				int valid_colors = 0;

				// Check diagonal pixels (top-left, top-right, bottom-left, bottom-right)
				if (x > 0 && y > 0) { // Top-left
					diagonal_colors[valid_colors++] = image[(y - 1) * width + (x - 1)];
				}
				if (x < width - 1 && y > 0) { // Top-right
					diagonal_colors[valid_colors++] = image[(y - 1) * width + (x + 1)];
				}
				if (x > 0 && y < height - 1) { // Bottom-left
					diagonal_colors[valid_colors++] = image[(y + 1) * width + (x - 1)];
				}
				if (x < width - 1 && y < height - 1) { // Bottom-right
					diagonal_colors[valid_colors++] = image[(y + 1) * width + (x + 1)];
				}

				// Count how many diagonal pixels are near the same color
				int similar_count = 0;
				uint32_t reference_color = diagonal_colors[0]; // Use the first color as reference
				for (int i = 0; i < valid_colors; i++) {
					if (is_near_same_color(reference_color, diagonal_colors[i], threshold)) {
						similar_count++;
					}
				}

				// If 3 or more diagonal pixels are similar, replace the black pixel
				if (similar_count >= 3) {
					*pixel = average_color(diagonal_colors, valid_colors);
				}
			}
		}
	}
}
