/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:59:36 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/15 12:52:09 by cjoao-de         ###   ########.fr       */
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

// void	free_scene(t_scene *scene)
// t_minirt *s
// {
// 	void	*tmp;

// 	tmp = NULL;
// 	while (scene->lights)
// 	{
// 		tmp = scene->lights->next;
// 		free(scene->lights->content);
// 		free(scene->lights);
// 		scene->lights = tmp;
// 	}
// 	while (scene->objects)
// 	{
// 		tmp = scene->objects->next;
// 		if (object_content(scene->objects)->mat.tex.texture_file)
// 		{
// 			free(object_content(scene->objects)->mat.tex.texture_file);
// 			//TODO other method for free, need t_xvar (mlx_ptr)
// 			// mlx_destroy_image(scene,
//				object_content(scene->objects)->mat.tex.texture.image);
// 		}
// 		free(scene->objects->content);
// 		free(scene->objects);
// 		scene->objects = tmp;
// 	}
// }

void	free_scene(t_minirt *s)
{
	t_list		*tmp;
	t_object	*obj;

	tmp = NULL;
	while (s->scene.lights)
	{
		tmp = s->scene.lights->next;
		free(s->scene.lights->content);
		free(s->scene.lights);
		s->scene.lights = tmp;
	}
	while (s->scene.objects)
	{
		tmp = s->scene.objects;
		obj = object_content(tmp);
		s->scene.objects = s->scene.objects->next;
		if (s->mlx && obj->mat.tex.texture.image)
			mlx_destroy_image(s->mlx, obj->mat.tex.texture.image);
		if (s->mlx && obj->mat.tex.texture_file)
			free(obj->mat.tex.texture_file);
		free(tmp->content);
		free(tmp);
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
	if (s->scene.cam.img.image)
		mlx_destroy_image(s->mlx, s->scene.cam.img.image);
	if (s->menu.img.image)
		mlx_destroy_image(s->mlx, s->menu.img.image);
}

int	end_minirt(t_minirt *s)
{
	free_images(s);
	if (s->win_rayt)
		free_scene(s);
	if (s->win_rayt)
		mlx_destroy_window(s->mlx, s->win_rayt);
	if (s->win_menu)
		mlx_destroy_window(s->mlx, s->win_menu);
	free(s->scene.cam.copy);
	free(s->scene.cam.red);
	free(s->scene.cam.cyan);
	free(s->scene.cam.anaglyph);
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	exit(0);
}
