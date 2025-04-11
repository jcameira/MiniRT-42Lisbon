/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/11 13:52:11 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

void	dup_image(char *dst, char *src)
{
	ft_memmove(dst, src, (W + 32) * H * 4);
}

void	restore_image(t_minirt *s, char *image)
{
	dup_image(s->scene.cam.img.data, image);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}

void	setup_buffers(t_minirt *s)
{
	// create_left_right(s);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
}
