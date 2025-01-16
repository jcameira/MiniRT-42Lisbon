/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:34:21 by jcameira          #+#    #+#             */
/*   Updated: 2025/01/14 15:17:22 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_parsed_elements(t_camera cam, t_scene scene)
{
	void	*tmp;

	printf("===============CAMERA===============\n");
	printf("Origin -> %f,%f,%f\n", cam.o[x], cam.o[y], cam.o[z]);
	printf("Normalized Vector -> %f,%f,%f\n", cam.nv[x], cam.nv[y], cam.nv[z]);
	printf("Fov -> %d\n", cam.fov);
	printf("===========AMBIENT LIGHT============\n");
	printf("Brithness -> %f\n", scene.al_br);
	printf("Color -> %d,%d,%d\n", scene.al_c.r, scene.al_c.g, scene.al_c.b);
	printf("===============LIGHTS===============\n");
	tmp = scene.lights;
	while (tmp)
	{
		printf("Origin -> %f,%f,%f\n", ((t_light *)tmp)->o[x], ((t_light *)tmp)->o[y], ((t_light *)tmp)->o[z]);
		printf("Brithness -> %f\n", ((t_light *)tmp)->br);
		printf("Color -> %d,%d,%d\n", ((t_light *)tmp)->c.r, ((t_light *)tmp)->c.g, ((t_light *)tmp)->c.b);
		printf("\n");
		tmp = ((t_light *)tmp)->next;
	}
	printf("===============FIGURES==============\n");
	tmp = scene.figures;
	while (tmp)
	{
		if (((t_figure *)tmp)->type == SP)
		{
			printf("SPHERE\n");
			printf("Origin -> %f,%f,%f\n", ((t_figure *)tmp)->f.sp.c[x], ((t_figure *)tmp)->f.sp.c[y], ((t_figure *)tmp)->f.sp.c[z]);
			printf("Radius -> %f\n", ((t_figure *)tmp)->f.sp.r);
		}
		if (((t_figure *)tmp)->type == PL)
		{
			printf("PLANE\n");
			printf("Point -> %f,%f,%f\n", ((t_figure *)tmp)->f.pl.p[x], ((t_figure *)tmp)->f.pl.p[y], ((t_figure *)tmp)->f.pl.p[z]);
			printf("Normalized Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.pl.nv[x], ((t_figure *)tmp)->f.pl.nv[y], ((t_figure *)tmp)->f.pl.nv[z]);
		}
		if (((t_figure *)tmp)->type == CY)
		{
			printf("CYLINDER\n");
			printf("Origin -> %f,%f,%f\n", ((t_figure *)tmp)->f.cy.c[x], ((t_figure *)tmp)->f.cy.c[y], ((t_figure *)tmp)->f.cy.c[z]);
			printf("Normalized Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.cy.nv[x], ((t_figure *)tmp)->f.cy.nv[y], ((t_figure *)tmp)->f.cy.nv[z]);
			printf("Diameter -> %f\n", ((t_figure *)tmp)->f.cy.r);
			printf("Height -> %f\n", ((t_figure *)tmp)->f.cy.h);
		}
		if (((t_figure *)tmp)->type == QU)
		{
			printf("QUADRILATERAL\n");
			printf("Point -> %f,%f,%f\n", ((t_figure *)tmp)->f.qu._q[x], ((t_figure *)tmp)->f.qu._q[y], ((t_figure *)tmp)->f.qu._q[z]);
			printf("First Side Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.qu.u[x], ((t_figure *)tmp)->f.qu.u[y], ((t_figure *)tmp)->f.qu.u[z]);
			printf("Second Side Vector -> %f,%f,%f\n", ((t_figure *)tmp)->f.qu.v[x], ((t_figure *)tmp)->f.qu.v[y], ((t_figure *)tmp)->f.qu.v[z]);
		}
		printf("Color -> %d,%d,%d\n", ((t_figure *)tmp)->c.r, ((t_figure *)tmp)->c.g, ((t_figure *)tmp)->c.b);
		printf("\n");
		tmp = ((t_figure *)tmp)->next;
	}
}

void	print_point(float p[3])
{
	printf("X -> %f\n", p[x]);
	printf("Y -> %f\n", p[y]);
	printf("Z -> %f\n", p[z]);
}
