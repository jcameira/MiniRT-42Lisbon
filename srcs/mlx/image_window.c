/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/02/10 21:15:36 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

void	dup_image(char *dst, char *src)
{
	// ft_memmove(s->cam.copy, s->cam.img.data, (W + 32) * H * 4);
	ft_memmove(dst, src, (W + 32) * H * 4);
	// return ;
}

void	restore_image(t_minirt *s, char *image)
{
	// ft_memmove(s->cam.img.data, image, (W + 32) * H * 4);
	dup_image(s->cam.img.data, image);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	// return ;
}
