/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:59:36 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 18:05:52 by cjoao-de         ###   ########.fr       */
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
		if (object_content(scene->objects)->mat.tex.texture_file)
		{
			free(object_content(scene->objects)->mat.tex.texture_file);
			mlx_destroy_image(scene, object_content(scene->objects)->mat.tex.texture.image);
		}
		free(scene->objects->content);
		free(scene->objects);

		scene->objects = tmp;
	}
}

static void	free_images(t_minirt *s)
{
	if (s->assets.bt_clrpick.img.image)
		mlx_destroy_image(s->mlx, s->assets.bt_clrpick.img.image);
	if (s->assets.bt_render.img.image)
		mlx_destroy_image(s->mlx, s->assets.bt_render.img.image);
	if (s->assets.label_figures.img.image)
		mlx_destroy_image(s->mlx, s->assets.label_figures.img.image);
	if (s->assets.label_materials.img.image)
		mlx_destroy_image(s->mlx, s->assets.label_materials.img.image);
	if (s->assets.bt_gradient.img.image)
		mlx_destroy_image(s->mlx, s->assets.bt_gradient.img.image);
	if (s->assets.ic_al.img.image)
		mlx_destroy_image(s->mlx, s->assets.ic_al.img.image);
	if (s->assets.ic_pl.img.image)
		mlx_destroy_image(s->mlx, s->assets.ic_pl.img.image);
	if (s->assets.ic_sl.img.image)
		mlx_destroy_image(s->mlx, s->assets.ic_sl.img.image);
	if (s->scene.cam.img.image)
		mlx_destroy_image(s->mlx, s->scene.cam.img.image);
	if (s->menu.img.image)
		mlx_destroy_image(s->mlx, s->menu.img.image);
}
int	end_minirt(t_minirt *s)
{
	free_images(s);
	if (s->win_rayt)
		mlx_destroy_window(s->mlx, s->win_rayt);
	if (s->win_menu)
		mlx_destroy_window(s->mlx, s->win_menu);
	free(s->scene.cam.copy);
	free(s->scene.cam.red);
	free(s->scene.cam.cyan);
	free(s->scene.cam.anaglyph);
	free(s->scene.cam.clean);
	mlx_destroy_display(s->mlx);
	free_scene(&s->scene);
	free(s->mlx);
	exit(0);
}
