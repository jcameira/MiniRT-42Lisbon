/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/03/12 13:47:57 by jcameira         ###   ########.fr       */
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
