/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:10 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 16:12:10 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	set_cone_info(t_object *content, char **info)
{
	vec3_normalizef(content->co.nv);
	content->co.r = ft_atof(info[3]) / 2;
	if (!in_range(content->co.r, 0.1, INFINITY))
		return (0);
	content->co.h = ft_atof(info[4]);
	if (!in_range(content->co.h, 0.1, INFINITY))
		return (0);
	content->hit = &hit_co;
	content->normal = &normal_co;
	content->uv = NULL;
	return (1);
}

int	add_cone_cap(t_scene *scene, t_object *content, char **info)
{
	t_object	*new_content;

	if (!set_cone_info(content, info))
		return (0);
	content->co.bot_cap = new_object();
	if (!content->co.bot_cap)
		return (ft_dprintf(2, NO_SPACE), 0);
	new_content = object_content(content->co.bot_cap);
	new_content->type = DS;
	if (!parse_material(&new_content->mat, info + 6))
		return (0);
	new_content->ds.r = content->co.r;
	parse_color(&new_content->mat.c, info[5]);
	vec3_copyf(new_content->ds.c, content->co.c);
	vec3_scalef(new_content->ds.c, content->co.nv, content->co.h);
	vec3_addf(new_content->ds.c, new_content->ds.c, content->co.c);
	vec3_copyf(new_content->ds.nv, content->cy.nv);
	new_content->hit = &hit_ds;
	new_content->normal = &normal_ds;
	content->cy.bot_cap->next = NULL;
	ft_lstadd_back(&scene->objects, content->co.bot_cap);
	return (1);
}

int	parse_cone(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 14)
		return (ft_dprintf(2, CONE_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = CO;
	if (!parse_point(&content->co.c, info[1], 0)
		|| !parse_point(&content->co.nv, info[2], 1)
		|| !check_if_float(info[3]) || !check_if_float(info[4])
		|| !parse_color(&content->mat.c, info[5])
		|| !parse_material(&content->mat, info + 6)
		|| !add_cone_cap(scene, content, info))
		return (ft_dprintf(2, CONE_USAGE), free(content),
			free_arr((void **)info), free(new), 0);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
