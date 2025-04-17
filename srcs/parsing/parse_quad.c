/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:21 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 05:36:24 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_quad_info(t_object *content)
{
	content->hit = &hit_qu;
	content->normal = &normal_qu;
	content->uv = &get_quad_uv;
}

int	parse_quad(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 13)
		return (ft_dprintf(2, QUAD_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = QU;
	if (!parse_point(&content->qu._q, info[1], 0)
		|| !parse_point(&content->qu.u, info[2], 0)
		|| !parse_point(&content->qu.v, info[3], 0)
		|| !parse_color(&content->mat.c, info[4])
		|| !parse_material(&content->mat, info + 5))
		return (ft_dprintf(2, QUAD_USAGE),
			free_arr((void **)info), free(new), 0);
	set_quad_info(content);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
