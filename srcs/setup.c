/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:52:39 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/16 05:04:42 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	setup_hooks(t_minirt *s)
{
	mlx_hook(s->win_rayt, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_menu, KeyPress, KeyPressMask, &handle_keypress, s);
	mlx_hook(s->win_rayt, DestroyNotify, StructureNotifyMask, &end_minirt, s);
	mlx_mouse_hook(s->win_menu, menu_mouse, (void *)s);
	return (0);
}

void	get_texture_imgs(t_minirt *s)
{
	t_list		*tmp_list;
	t_object	*obj;

	tmp_list = s->scene.objects;
	while (tmp_list)
	{
		obj = object_content(tmp_list);
		if ((obj->mat.tex.type == image || obj->mat.tex.type == bump_map) && ft_strcmp(obj->mat.tex.img_texture_file, "-"))
		{
			printf("File: %s\n", obj->mat.tex.img_texture_file);
			obj->mat.tex.img_texture.image = mlx_xpm_file_to_image(s->mlx,
				obj->mat.tex.img_texture_file, &obj->mat.tex.img_texture.width,
				&obj->mat.tex.img_texture.height);
			if (obj->mat.tex.img_texture.image == NULL)
			{
				ft_dprintf(2, FILE_NOT_FOUND, obj->mat.tex.img_texture_file);
				free(obj->mat.tex.img_texture_file);
				end_minirt(s);
			}
			obj->mat.tex.img_texture.data = mlx_get_data_addr(obj->mat.tex.img_texture.image, &obj->mat.tex.img_texture.bpp,
				&obj->mat.tex.img_texture.size_line, &obj->mat.tex.img_texture.type);
		}
		if (obj->mat.tex.type == bump_map && ft_strcmp(obj->mat.tex.bump_texture_file, "-"))
		{
			obj->mat.tex.img_texture.data = mlx_get_data_addr(obj->mat.tex.img_texture.image, &obj->mat.tex.img_texture.bpp,
				&obj->mat.tex.img_texture.size_line, &obj->mat.tex.img_texture.type);
			printf("File: %s\n", obj->mat.tex.bump_texture_file);
			obj->mat.tex.bump_texture.image = mlx_xpm_file_to_image(s->mlx,
				obj->mat.tex.bump_texture_file, &obj->mat.tex.bump_texture.width,
				&obj->mat.tex.bump_texture.height);
			if (obj->mat.tex.bump_texture.image == NULL)
			{
				ft_dprintf(2, FILE_NOT_FOUND, obj->mat.tex.bump_texture_file);
				free(obj->mat.tex.bump_texture_file);
				end_minirt(s);
			}
			obj->mat.tex.bump_texture.data = mlx_get_data_addr(obj->mat.tex.bump_texture.image, &obj->mat.tex.bump_texture.bpp,
				&obj->mat.tex.bump_texture.size_line, &obj->mat.tex.bump_texture.type);
		}
		tmp_list = tmp_list->next;
	}
}

bool	setup_rayt(t_minirt *s)
{
	s->win_rayt = mlx_new_window(s->mlx, W, H, WINDOW_NAME);
	if (s->win_rayt == NULL)
		return (false);
	s->scene.cam.img.image = mlx_new_image(s->mlx, W, H);
	s->scene.cam.img.height = H;
	s->scene.cam.img.width = W;
	s->scene.cam.copy = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.red = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.cyan = ft_calloc((W + 32) * H * 4, 1);
	s->scene.cam.anaglyph = ft_calloc((W + 32) * H * 4, 1);
	if (!s->scene.cam.copy || !s->scene.cam.red || !s->scene.cam.cyan \
		|| !s->scene.cam.anaglyph || s->scene.cam.img.image == NULL)
		return (false);
	s->scene.cam.img.data = mlx_get_data_addr(s->scene.cam.img.image, \
		&s->scene.cam.img.bpp, &s->scene.cam.img.size_line, \
		&s->scene.cam.img.type);
	if (s->scene.cam.img.data == 0)
		return (false);
	get_texture_imgs(s);
	s->scene.loop = false;
	s->scene.loop_ctr = 0;
	return (true);
}
