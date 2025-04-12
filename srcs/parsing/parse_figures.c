/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:07:51 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/12 11:42:18 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a sphere element that sets the information for
// the type of figure it is, its center, and its diameter as well as adding it
// to the back of the figure list
int	parse_sphere(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;

	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), 0);
	content = object_content(new);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->sp.c, line, 0))
		return (ft_dprintf(2, SPHERE_USAGE), free(content), free(new), 0);
	skip_info(&line);
	content->sp.r = ft_atof(line) / 2;
	skip_info(&line);
	if (!parse_color(&content->mat.c, line))
		return (ft_dprintf(2, SPHERE_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_material(&content->mat, line))
		return (ft_dprintf(2, SPHERE_USAGE), free(content), free(new), 0);
	content->print = &print_sphere;
	content->hit = &hit_sp;
	content->normal = &normal_sp;
	new->next = NULL;
	ft_lstadd_back(&scene->objects, new);
	return (1);
}

// General parsing function for a plane element that sets the information
// for the type of figure it is, a point in the plane, and a 3D normalized
// vector as well as adding it to the back of the figure list
int	parse_plane(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;

	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), 0);
	content = object_content(new);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->pl.p, line, 0))
		return (ft_dprintf(2, PLANE_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_point(&content->pl.nv, line, 1))
		return (ft_dprintf(2, PLANE_USAGE), free(content), free(new), 0);
	vec3_normalizef(content->pl.nv);
	skip_info(&line);
	if (!parse_color(&content->mat.c, line))
		return (ft_dprintf(2, PLANE_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_material(&content->mat, line))
		return (ft_dprintf(2, PLANE_USAGE), free(content), free(new), 0);
	content->print = &print_plane;
	content->hit = &hit_pl;
	content->normal = &normal_pl;
	new->next = NULL;
	ft_lstadd_back(&scene->objects, new);
	return (1);
}

//int	add_caps(t_scene *scene, t_object *content)
//{
//	content->cy.top_cap = ft_calloc(1, sizeof(t_object));
//	if (!content->cy.top_cap)
//		return (ft_dprintf(2, NO_SPACE), 0);
//	content->cy.top_cap->mat = content->mat;
//	content->cy.top_cap->hit = &hit_ds;
//	content->cy.top_cap->normal = &normal_ds;
//	content->cy.top_cap->ds.r = content->cy.r;
//	vec3_scalef(content->cy.top_cap->ds.c, content->cy.nv, content->cy.h / 2.0);
//	vec3_addf(content->cy.top_cap->ds.c, content->cy.top_cap->ds.c, content->cy.c);
//}

// General parsing function for a cylinder element that sets the information
// for the type of figure it is, its center, a 3D normalized vector, the
// diameter of its bases, and its height as well as adding it to the back of
// the figure list
// ? should probably just change the diameter to the radius for easier use
int	parse_cylinder(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;

	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), 0);
	content = object_content(new);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->cy.c, line, 0))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_point(&content->cy.nv, line, 1))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content), free(new), 0);
	vec3_normalizef(content->cy.nv);
	skip_info(&line);
	content->cy.r = ft_atof(line) / 2;
	skip_info(&line);
	content->cy.h = ft_atof(line);
	skip_info(&line);
	if (!parse_color(&content->mat.c, line))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_material(&content->mat, line))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content), free(new), 0);
	//if (!add_caps(scene, content))
	//	return (0);
	content->print = &print_cylinder;
	content->hit = &hit_cy;
	content->normal = &normal_cy;
	new->next = NULL;
	ft_lstadd_back(&scene->objects, new);
	return (1);
}

int	parse_quad(t_scene *scene, char *line)
{
	t_list		*new;
	t_object	*content;

	new = new_object();
	if (!new)
		return (ft_dprintf(2, NO_SPACE), 0);
	content = object_content(new);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->qu._q, line, 0))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_point(&content->qu.u, line, 0))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_point(&content->qu.v, line, 0))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_color(&content->mat.c, line))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	skip_info(&line);
	if (!parse_material(&content->mat, line))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	content->print = &print_quadrilateral;
	content->hit = &hit_qu;
	content->normal = &normal_qu;
	new->next = NULL;
	ft_lstadd_back(&scene->objects, new);
	return (1);
}
