/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:59:36 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/24 06:27:26 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_scene(t_scene *scene)
{
	void	*tmp;

	tmp = NULL;
	while (scene->lights)
	{
		tmp = scene->lights->next;
		free(scene->lights->content);
		free(scene->lights);
		scene->lights = tmp;
	}
	while (scene->objects)
	{
		tmp = scene->objects->next;
		free(scene->objects->content);
		free(scene->objects);
		scene->objects = tmp;
	}
}

int	end_minirt(t_minirt *s)
{
	mlx_destroy_image(s->mlx, s->scene.cam.img.image);
	mlx_destroy_image(s->mlx, s->menu.img.image);
	mlx_destroy_window(s->mlx, s->win_rayt);
	mlx_destroy_window(s->mlx, s->win_menu);
	free(s->cam.copy);
	free(s->cam.red);
	free(s->cam.cyan);
	free(s->cam.anaglyph);
	free(s->cam.clean);
	// mlx_destroy_image(s->mlx, &s->assets.bt_clrpick);
	// mlx_destroy_image(s->mlx, &s->assets.bt_render);
	// mlx_destroy_image(s->mlx, &s->assets.ic_al);
	// mlx_destroy_image(s->mlx, &s->assets.ic_pl);
	// mlx_destroy_image(s->mlx, &s->assets.ic_sl);
	mlx_destroy_display(s->mlx);
	free_scene(&s->scene);
	free(s->mlx);
	exit(0);
}
