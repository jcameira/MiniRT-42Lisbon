/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/06 20:24:39 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Apply horizontal shift to image pixels
void applyDepthShift(char *buffer, int shift, int dir)
{
	char *temp;
	int dest_x;
	int pixels = (W + 32) * H;
	int x;
	int y;

	temp = ft_calloc(pixels * 4, 1);	// Allocate temporary buffer
	if (!temp)
		return;
	shift *= dir;
	y = -1;		// Process each row
	while (y++ < H) {
		x = 0;
		while (x < W) {
			dest_x = x + shift;
			if (dest_x >= 0 && dest_x < W) {
				// Calculate pixel indices with correct stride
				// int sourceIdx = (y * (W + 32) + x) * 4;
				// int destIdx = (y * (W + 32) + dest_x) * 4;
				// Copy pixel (all 4 bytes - ARGB)
				// *(unsigned int*)(temp + destIdx) = *(unsigned int*)(buffer + sourceIdx);
				*(unsigned int *)(temp + (y * (W + 32) + dest_x) * 4) = \
					*(unsigned int *)(buffer + (y * (W + 32) + x) * 4);
			}
			x++;
		}
	}
	ft_memmove(buffer, temp, pixels * 4);	// Copy shifted data back to original buffer
	free(temp);
}

// Complete anaglyph creation workflow
void create_anaglyph_main(t_minirt *s)
{
	int shift = (int)(W * 0.02); // 2% of image width
	int i;

	if (!s->cam.copy || !s->cam.red || !s->cam.cyan || !s->cam.anaglyph)
	{
		if (!s->cam.red || !s->cam.cyan || !s->cam.anaglyph)
			return;
		if (!s->cam.anaglyph)
			s->cam.anaglyph = malloc(s->cam.pixels * 4);
	}
	ft_bzero(s->cam.anaglyph, s->cam.pixels * 4);
	create_left_right(s);	// Create red and cyan channel images
	applyDepthShift(s->cam.red, shift, -1);		// Shift red left
	applyDepthShift(s->cam.cyan, shift, 1);		// Shift cyan right
	// Merge channels into final anaglyph
	unsigned int *red_ptr = (unsigned int *)s->cam.red;
	unsigned int *cyan_ptr = (unsigned int *)s->cam.cyan;
	unsigned int *anaglyph_ptr = (unsigned int *)s->cam.anaglyph;
	i = -1;
	while (i++ < s->cam.pixels)
		anaglyph_ptr[i] = (red_ptr[i] & 0x00FF0000) | (cyan_ptr[i] & 0xFF00FFFF);
	dup_image(s->cam.img.data, s->cam.anaglyph);		// Display the anaglyph
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
}

/*
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
*/

// merge red and cyan images
// t_camera *vp	struct with prt to all images in program
// int shift	value for depth effect
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
			vp->anaglyph[pixelIdx] = shift_red[pixelIdx];
			// Green and blue channels from shifted cyan image
			vp->anaglyph[pixelIdx + 1] = shift_cyan[pixelIdx + 1];
			vp->anaglyph[pixelIdx + 2] = shift_cyan[pixelIdx + 2];
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
	// int			shiftAmount;
	// char		*shift_red;
	// char		*shift_cyan;

	// shift_red = ft_calloc((W + 32) * H * 4, 1);
	// shift_cyan = ft_calloc((W + 32) * H * 4, 1);
	vp = s->cam;
	create_left_right(s);
	// Calculate shift amount (e.g., 2% of image width)
	int shift = (int)(W * 0.02);
	// Create final anaglyph
	// vp.anaglyph = create_anaglyph(&vp, shift);
	create_anaglyph(&vp, shift);
	// free(shift_red);
	// free(shift_cyan);
}
