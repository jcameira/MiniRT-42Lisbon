/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:08:45 by jcameira          #+#    #+#             */
/*   Updated: 2025/04/16 12:09:14 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calc_viewport_info(t_scene *scene)
{
	float	temp[3];

	vec3_subf(temp, scene->cam.o, scene->cam.nv);
	scene->vp.fl = vec3_lenf(temp);
	scene->vp.v_height = 2 * tan(to_rad(scene->cam.fov) / 2) * scene->vp.fl;
	scene->vp.v_width = scene->vp.v_height * ((float)W / H);
	vec3_scalef(scene->vp.vh, scene->cam.u, scene->vp.v_width);
	vec3_scalef(scene->vp.deltah, scene->vp.vh, (float)1.0 / W);
	vec3_scalef(scene->vp.vv, scene->cam.v, -scene->vp.v_height);
	vec3_scalef(scene->vp.deltav, scene->vp.vv, (float)1.0 / H);
	scene->vp.vul[x] = scene->cam.o[x] - (scene->vp.fl * scene->cam.w[x])
		- (scene->vp.vh[x] / 2) - (scene->vp.vv[x] / 2);
	scene->vp.vul[y] = scene->cam.o[y] - (scene->vp.fl * scene->cam.w[y])
		- (scene->vp.vh[y] / 2) - (scene->vp.vv[y] / 2);
	scene->vp.vul[z] = scene->cam.o[z] - (scene->vp.fl * scene->cam.w[z])
		- (scene->vp.vh[z] / 2) - (scene->vp.vv[z] / 2);
	scene->vp.pixel00l[x] = scene->vp.vul[x]
		+ (0.5 * (scene->vp.deltah[x] + scene->vp.deltav[x]));
	scene->vp.pixel00l[y] = scene->vp.vul[y]
		+ (0.5 * (scene->vp.deltah[y] + scene->vp.deltav[y]));
	scene->vp.pixel00l[z] = scene->vp.vul[z]
		+ (0.5 * (scene->vp.deltah[z] + scene->vp.deltav[z]));
}

void	cam_prepare_vp(t_scene *scene)
{
	scene->cam.vup[x] = 0;
	scene->cam.vup[y] = 1;
	scene->cam.vup[z] = 0;
	vec3_subf(scene->cam.w, scene->cam.o, scene->cam.nv);
	vec3_normalizef(scene->cam.w);
	vec3_crossf(scene->cam.u, scene->cam.vup, scene->cam.w);
	vec3_normalizef(scene->cam.u);
	vec3_crossf(scene->cam.v, scene->cam.w, scene->cam.u);
	scene->cam.pixels = (W + 32) * H;
	scene->cam.has_cam = 1;
}
