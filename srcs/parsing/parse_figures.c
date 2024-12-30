/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:07:51 by jcameira          #+#    #+#             */
/*   Updated: 2024/12/30 14:36:03 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// General parsing function for a sphere element that sets the information for
// the type of figure it is, its center, and its diameter as well as adding it
// to the back of the figure list
// ? should probably just change the diameter to the radius for easier use
int	parse_sphere(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = SP;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.sp.c, line, 0))
		return (ft_fprintf(2, SPHERE_USAGE), free(new_f), 0);
	skip_info(&line);
	new_f->f.sp.r = ft_atof(line) / 2;
	skip_info(&line);
	if (!parse_color(&new_f->c, line))
		return (ft_fprintf(2, SPHERE_USAGE), free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}

// General parsing function for a plane element that sets the information
// for the type of figure it is, a point in the plane, and a 3D normalized
// vector as well as adding it to the back of the figure list
int	parse_plane(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = PL;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.pl.p, line, 0))
		return (ft_fprintf(2, PLANE_USAGE), free(new_f), 0);
	skip_info(&line);
	if (!parse_point(&new_f->f.pl.nv, line, 1))
		return (ft_fprintf(2, PLANE_USAGE), free(new_f), 0);
	vec3_normalizef(new_f->f.pl.nv);
	skip_info(&line);
	if (!parse_color(&new_f->c, line))
		return (ft_fprintf(2, PLANE_USAGE), free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}

// General parsing function for a cylinder element that sets the information
// for the type of figure it is, its center, a 3D normalized vector, the
// diameter of its bases, and its height as well as adding it to the back of
// the figure list
// ? should probably just change the diameter to the radius for easier use
int	parse_cylinder(t_scene *scene, char *line)
{
	t_figure	*new_f;

	new_f = malloc(sizeof(t_figure));
	if (!new_f)
		return (ft_fprintf(2, NO_SPACE), 0);
	new_f->type = CY;
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&new_f->f.cy.c, line, 0))
		return (ft_fprintf(2, CYLINDER_USAGE), free(new_f), 0);
	skip_info(&line);
	if (!parse_point(&new_f->f.cy.nv, line, 1))
		return (ft_fprintf(2, CYLINDER_USAGE), free(new_f), 0);
	vec3_normalizef(new_f->f.pl.nv);
	skip_info(&line);
	new_f->f.cy.r = ft_atof(line) / 2;
	skip_info(&line);
	new_f->f.cy.h = ft_atof(line);
	skip_info(&line);
	if (!parse_color(&new_f->c, line))
		return (ft_fprintf(2, CYLINDER_USAGE), free(new_f), 0);
	new_f->next = NULL;
	ft_lstadd_back((t_list **)&scene->figures, (t_list *)new_f);
	return (1);
}
