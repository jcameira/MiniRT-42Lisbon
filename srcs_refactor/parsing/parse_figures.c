/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:07:51 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/12 12:14:05 by jcameira         ###   ########.fr       */
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
	//new->type = SP;
	content = object_content(new);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->sp.c, line, 0))
		return (ft_dprintf(2, SPHERE_USAGE), free(content), free(new), 0);
	skip_info(&line);
	content->sp.r = ft_atof(line) / 2;
	skip_info(&line);
	if (!parse_color(&content->c, line))
		return (ft_dprintf(2, SPHERE_USAGE), free(content), free(new), 0);
	content->print = &print_sphere;
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
	//new->type = PL;
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
	if (!parse_color(&content->c, line))
		return (ft_dprintf(2, PLANE_USAGE), free(content), free(new), 0);
	content->print = &print_plane;
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
	//new->type = CY;
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
	if (!parse_color(&content->c, line))
		return (ft_dprintf(2, CYLINDER_USAGE), free(content), free(new), 0);
	content->print = &print_cylinder;
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
	//new->type = QU;
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
	if (!parse_color(&content->c, line))
		return (ft_dprintf(2, QUAD_USAGE), free(content), free(new), 0);
	content->print = &print_quadrilateral;
	new->next = NULL;
	ft_lstadd_back(&scene->objects, new);
	return (1);
}
