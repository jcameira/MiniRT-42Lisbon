/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:12:14 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/17 15:13:44 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	set_cylinder_info(t_object *content, char **info)
{
	vec3_normalizef(content->cy.nv);
	content->cy.r = ft_atof(info[3]) / 2;
	content->cy.h = ft_atof(info[4]);
	content->hit = &hit_cy;
	content->normal = &normal_cy;
	content->uv = NULL;
}

int	add_bot_cap(t_scene *scene, t_object *content, char **info)
{
	t_object	*new_content;

	content->cy.bot_cap = new_object();
	if (!content->cy.bot_cap)
		return (ft_dprintf(2, NO_SPACE), 0);
	new_content = object_content(content->cy.bot_cap);
	new_content->type = DS;
	if (!parse_material(&new_content->mat, info + 6))
		return (0);
	new_content->ds.r = content->cy.r;
	parse_color(&new_content->mat.c, info[5]);
	vec3_scalef(new_content->ds.c, content->cy.nv, content->cy.h / (-2.0));
	vec3_addf(new_content->ds.c, new_content->ds.c, content->cy.c);
	vec3_scalef(new_content->ds.nv, content->cy.nv, -1.0);
	new_content->hit = &hit_ds;
	new_content->normal = &normal_ds;
	new_content->uv = NULL;
	content->cy.bot_cap->next = NULL;
	ft_lstadd_back(&scene->objects, content->cy.bot_cap);
	return (1);
}

int	add_top_cap(t_scene *scene, t_object *content, char **info)
{
	t_object	*new_content;

	set_cylinder_info(content, info);
	content->cy.top_cap = new_object();
	if (!content->cy.top_cap)
		return (ft_dprintf(2, NO_SPACE), 0);
	new_content = object_content(content->cy.top_cap);
	new_content->type = DS;
	if (!parse_material(&new_content->mat, info + 6))
		return (0);
	new_content->ds.r = content->cy.r;
	parse_color(&new_content->mat.c, info[5]);
	vec3_scalef(new_content->ds.c, content->cy.nv, content->cy.h / 2.0);
	vec3_addf(new_content->ds.c, new_content->ds.c, content->cy.c);
	vec3_copyf(new_content->ds.nv, content->cy.nv);
	new_content->hit = &hit_ds;
	new_content->normal = &normal_ds;
	new_content->uv = NULL;
	content->cy.top_cap->next = NULL;
	ft_lstadd_back(&scene->objects, content->cy.top_cap);
	if (!add_bot_cap(scene, content, info))
		return (0);
	return (1);
}

// General parsing function for a cylinder element that sets the information
// for the type of figure it is, its center, a 3D normalized vector, the
// diameter of its bases, and its height as well as adding it to the back of
// the figure list
// ? should probably just change the diameter to the radius for easier use
int	parse_cylinder(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;
	char		**info;

	info = ft_split(line, ' ');
	if (!info)
		return (ft_dprintf(2, NO_SPACE), 0);
	if (arr_size(info) != 14)
		return (ft_dprintf(2, CYLINDER_USAGE), free_arr((void **)info), 0);
	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), free_arr((void **)info), 0);
	content = object_content(new);
	content->type = CY;
	if (!parse_point(&content->cy.c, info[1], 0)
		|| !parse_point(&content->cy.nv, info[2], 1)
		|| !check_if_float(info[3]) || !check_if_float(info[4])
		|| !parse_color(&content->mat.c, info[5])
		|| !parse_material(&content->mat, info + 6)
		|| !add_top_cap(scene, content, info))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content),
			free_arr((void **)info), free(new), 0);
	new->next = NULL;
	return (ft_lstadd_back(&scene->objects, new), free_arr((void **)info), 1);
}
