/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:59:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/10/28 21:12:13 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_scene(t_scene *scene)
{
	void	*tmp;

	while (scene->lights)
	{
		tmp = scene->lights->next;
		free(scene->lights);
		scene->lights = tmp;
	}
	while (scene->figures)
	{
		tmp = scene->figures->next;
		free(scene->figures);
		scene->figures = tmp;
	}
}

int	end_minirt(t_minirt *s)
{
	mlx_destroy_image(s->mlx_ptr, s->cam.img.image);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_display(s->mlx_ptr);
	free_scene(&s->scene);
	free(s->mlx_ptr);
	exit(0);
}
