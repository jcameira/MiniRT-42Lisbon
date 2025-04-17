/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:19 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 15:13:51 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_plane_info(t_object *content)
{
	vec3_normalizef(content->pl.nv);
	content->hit = &hit_pl;
	content->normal = &normal_pl;
	content->uv = NULL;
}

// General parsing function for a plane element that sets the information
// for the type of figure it is, a point in the plane, and a 3D normalized
// vector as well as adding it to the back of the figure list
int	parse_plane(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 12)
		return (ft_dprintf(2, PLANE_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = PL;
	if (!parse_point(&content->pl.p, info[1], 0)
		|| !parse_point(&content->pl.nv, info[2], 1)
		|| !parse_color(&content->mat.c, info[3])
		|| !parse_material(&content->mat, info + 4))
		return (ft_dprintf(2, PLANE_USAGE), free(content),
			free_arr((void **)info), free(new), 0);
	set_plane_info(content);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
