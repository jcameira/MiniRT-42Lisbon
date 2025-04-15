/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:34:21 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/15 16:47:52 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_sphere(t_list *object)
{
	t_object	*content;

	content = object_content(object);
	printf("SPHERE\n");
	printf("Origin -> %f,%f,%f\n", content->sp.c[x], content->sp.c[y], content->sp.c[z]);
	printf("Radius -> %f\n", content->sp.r);
	printf("Color -> %d,%d,%d\n", content->mat.c.r, content->mat.c.g, content->mat.c.b);
	printf("Material type -> %d\n", content->mat.type);
	printf("Fuzz -> %f\n", content->mat.fuzz);
	ft_dprintf(2, "object type: %i\n", object_type(object));
}

void	print_plane(t_list *object)
{
	t_object	*content;

	content = object_content(object);
	printf("PLANE\n");
	printf("Point -> %f,%f,%f\n", content->pl.p[x], content->pl.p[y], content->pl.p[z]);
	printf("Normalized Vector -> %f,%f,%f\n", content->pl.nv[x], content->pl.nv[y], content->pl.nv[z]);
	printf("Color -> %d,%d,%d\n", content->mat.c.r, content->mat.c.g, content->mat.c.b);
	ft_dprintf(2, "object type: %i\n", object_type(object));
}

void	print_cylinder(t_list *object)
{
	t_object	*content;

	content = object_content(object);
	printf("CYLINDER\n");
	printf("Origin -> %f,%f,%f\n", content->cy.c[x], content->cy.c[y], content->cy.c[z]);
	printf("Normalized Vector -> %f,%f,%f\n", content->cy.nv[x], content->cy.nv[y], content->cy.nv[z]);
	printf("Diameter -> %f\n", content->cy.r);
	printf("Height -> %f\n", content->cy.h);
	printf("Color -> %d,%d,%d\n", content->mat.c.r, content->mat.c.g, content->mat.c.b);
}

void	print_quadrilateral(t_list *object)
{
	t_object	*content;

	content = object_content(object);
	printf("QUADRILATERAL\n");
	printf("Point -> %f,%f,%f\n", content->qu._q[x], content->qu._q[y], content->qu._q[z]);
	printf("First Side Vector -> %f,%f,%f\n", content->qu.u[x], content->qu.u[y], content->qu.u[z]);
	printf("Second Side Vector -> %f,%f,%f\n", content->qu.v[x], content->qu.v[y], content->qu.v[z]);
	printf("Color -> %d,%d,%d\n", content->mat.c.r, content->mat.c.g, content->mat.c.b);
	ft_dprintf(2, "object type: %i\n", object_type(object));
}

void	print_parsed_elements(t_scene scene)
{
	t_list		*tmp;
	//t_object	*obj;

	printf("===============CAMERA===============\n");
	printf("Origin -> %f,%f,%f\n", scene.cam.o[x], scene.cam.o[y], scene.cam.o[z]);
	printf("Normalized Vector -> %f,%f,%f\n", scene.cam.nv[x], scene.cam.nv[y], scene.cam.nv[z]);
	printf("Fov -> %d\n", scene.cam.fov);
	printf("===========AMBIENT LIGHT============\n");
	printf("Brithness -> %f\n", scene.amb.al_br);
	printf("Color -> %d,%d,%d\n", scene.amb.al_c.r, scene.amb.al_c.g, scene.amb.al_c.b);
	printf("===============LIGHTS===============\n");
	tmp = scene.lights;
	while (tmp)
	{
		//obj = light_content(tmp)->obj;
		printf("\n");
		tmp = tmp->next;
	}
	printf("===============OBJECTS==============\n");
	tmp = scene.objects;
	while (tmp)
	{
		if (object_content(tmp)->print)
			object_content(tmp)->print(tmp);
		printf("\n");
		tmp = tmp->next;
	}
}

void	print_point(float p[3])
{
	printf("X -> %f\n", p[x]);
	printf("Y -> %f\n", p[y]);
	printf("Z -> %f\n", p[z]);
}
