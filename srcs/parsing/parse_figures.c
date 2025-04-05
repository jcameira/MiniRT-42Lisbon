/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:07:51 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/05 16:14:44 by cjoao-de         ###   ########.fr       */
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
	content->type = SP;
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
	content->type = PL;
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
	vec3_normalizef(content->pl.nv);
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
	content->print = &print_cylinder;
	//content->hit = &hit_cy;
	//content->normal = &normal_cy;
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
	content->type = QU;
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
