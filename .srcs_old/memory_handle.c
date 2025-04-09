/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:59:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/26 20:19:21 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_scene(t_scene *scene)
{
	void	*tmp;

	tmp = NULL;
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
	mlx_destroy_image(s->mlx, s->cam.img.image);
	mlx_destroy_image(s->mlx, s->menu.img.image);
	mlx_destroy_window(s->mlx, s->win_rayt);
	mlx_destroy_window(s->mlx, s->win_menu);
	mlx_destroy_display(s->mlx);
	free_scene(&s->scene);
	free(s->mlx);
	exit(0);
}
