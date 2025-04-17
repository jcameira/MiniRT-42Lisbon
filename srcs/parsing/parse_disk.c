/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:16 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 05:24:42 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_disk_info(t_object *content, char **info)
{
	vec3_normalizef(content->ds.nv);
	content->ds.r = ft_atof(info[3]) / 2;
	content->hit = &hit_ds;
	content->normal = &normal_ds;
	content->uv = NULL;
}

int	parse_disk(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 13)
		return (ft_dprintf(2, CONE_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = DS;
	if (!parse_point(&content->ds.c, info[1], 0)
		|| !parse_point(&content->ds.nv, info[2], 1)
		|| !check_if_float(info[3]) || !parse_color(&content->mat.c, info[4])
		|| !parse_material(&content->mat, info + 5))
		return (ft_dprintf(2, DISK_USAGE),
			free_arr((void **)info), free(new), 0);
	set_disk_info(content, info);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
