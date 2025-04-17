/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:24 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 15:13:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_sphere_info(t_object *content, char **info)
{
	content->sp.r = ft_atof(info[2]) / 2;
	content->hit = &hit_sp;
	content->normal = &normal_sp;
	content->uv = &get_sphere_uv;
}

// General parsing function for a sphere element that sets the information for
// the type of figure it is, its center, and its diameter as well as adding it
// to the back of the figure list
int	parse_sphere(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 12)
		return (ft_dprintf(2, SPHERE_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = SP;
	if (!parse_point(&content->sp.c, info[1], 0)
		|| !check_if_float(info[2])
		|| !parse_color(&content->mat.c, info[3])
		|| !parse_material(&content->mat, info + 4))
		return (ft_dprintf(2, SPHERE_USAGE), free(content),
			free_arr((void **)info), free(new), 0);
	set_sphere_info(content, info);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
