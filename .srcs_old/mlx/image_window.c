/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:45:50 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/14 20:32:50 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minirt.h>

void	dup_image(t_minirt *s)
{
	ft_memmove( s->cam.copy, s->cam.img.data, (W + 32) * H * 4);
	return ;
}

void	restore_image(t_minirt *s)
{
	ft_memmove(s->cam.img.data, s->cam.copy, (W + 32) * H * 4);
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	return ;
}



//   if (!(img->data = m
// malloc((width+32)*height*4)
