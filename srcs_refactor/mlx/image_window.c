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

void	dup_image(t_minirt *s)
{
	ft_memmove(s->scene.cam.copy, s->scene.cam.img.data, (W + 32) * H * 4);
	return ;
}

void	restore_image(t_minirt *s)
{
	ft_memmove(s->scene.cam.img.data, s->scene.cam.copy, (W + 32) * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->scene.cam.img.image, 0, 0);
	return ;
}



//   if (!(img->data = m
// malloc((width+32)*height*4)
