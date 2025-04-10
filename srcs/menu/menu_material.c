/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:45:03 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/10 18:25:08 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	change_material(t_list *object, int type, t_obj_scatter	scatter, \
	float br, char *message)
{
	t_object	*content;

	content = object_content(object);
	content->mat.type = type;
	if (br != 2.0 && content->mat.br == 0.0)
		content->mat.br = br;
	if (scatter != NULL)
		content->mat.scatter = scatter;
	// content->mat.tex.type = 1 // solid color
	// content->mat.tex.type = 2 // checkered
	// content->mat.tex.type = 3 // texture
	// content->mat.tex.type = 4 // bump map
	ft_printf("\n%s\n", message);
}


void	set_material(t_list *object, int keysym)
{
	// t_object	*content;

	// content = object_content(object);
	if (keysym == XK_1)
		change_material(object, 1, lambertian_scatter, 2.0, "Lambertian");
	else if (keysym == XK_2)
		change_material(object, 2, specular_scatter, 2.0, "Specular");
	else if (keysym == XK_3)
		change_material(object, 3, dialetric_scatter, 2.0, "Dialetric");
	else if (keysym == XK_4)
		//TODO check with jcameira if no scatter is OK
		change_material(object, 4, NULL, 1, "Light ON");
	else
		set_advanced_material(object, keysym);
}

void	set_advanced_material(t_list *object, int keysym)
{

	t_object	*content;

	content = object_content(object);
	if (keysym == XK_5)
	{
		change_material(object, 4, NULL, 1, "Light ON");
		// content->mat.type = 5;
		//! todo get types
		content->mat.tex.type = 5;
		// content->mat.scatter = &checkboard_scatter;
		ft_printf("\n%s\n", "Checkerboard");
	}
	if (keysym == XK_6)
	{
		content->mat.type = 6;
		// content->mat.scatter = &texture_scatter;
		ft_printf("\n%s\n", "Texture");
	}
	// todo all of this
	// content->mat.tex.type = 1 // solid color
	// content->mat.tex.type = 2 // checkered
	// content->mat.tex.type = 3 // texture
	// content->mat.tex.type = 4 // bump map
}
