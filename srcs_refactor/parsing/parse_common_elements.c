/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:12:09 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/24 05:15:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	calc_viewport_info(t_scene *scene)
{
	//float	temp[3];

	//vec3_subf(temp, scene->cam.o, scene->cam.nv);
	//scene->vp.fl = vec3_lenf(temp);
	//scene->vp.v_height = 2 * tan(to_rad(scene->cam.fov) / 2) * scene->vp.fl;
	//scene->vp.v_width = scene->vp.v_height * ((float)W / H);
	//vec3_scalef(scene->vp.vh, scene->cam.u, scene->vp.v_width);
	//vec3_scalef(scene->vp.deltah, scene->vp.vh, (float)1 / W);
	//vec3_scalef(scene->vp.vv,scene->cam.v, -scene->vp.v_height);
	//vec3_scalef(scene->vp.deltav, scene->vp.vv, (float)1 / H);
	//scene->vp.vul[x] = scene->cam.o[x] - (scene->vp.fl * scene->cam.w[x]) - (scene->vp.vh[x] / 2) - (scene->vp.vv[x] / 2);
	//scene->vp.vul[y] = scene->cam.o[y] - (scene->vp.fl * scene->cam.w[y]) - (scene->vp.vh[y] / 2) - (scene->vp.vv[y] / 2);
	//scene->vp.vul[z] = scene->cam.o[z] - (scene->vp.fl * scene->cam.w[z]) - (scene->vp.vh[z] / 2) - (scene->vp.vv[z] / 2);
	//scene->vp.pixel00l[x] = scene->vp.vul[x] + (0.5 * (scene->vp.deltah[x] + scene->vp.deltav[x]));
	//scene->vp.pixel00l[y] = scene->vp.vul[y] + (0.5 * (scene->vp.deltah[y] + scene->vp.deltav[y]));
	//scene->vp.pixel00l[z] = scene->vp.vul[z] + (0.5 * (scene->vp.deltah[z] + scene->vp.deltav[z]));
	scene->vp.fl = 1;
	scene->vp.v_height = 2.0;
	scene->vp.v_width = scene->vp.v_height * ((float)W / H);
	scene->vp.vh[x] = scene->vp.v_width;
	scene->vp.vh[y] = 0;
	scene->vp.vh[z] = 0;
	vec3_scalef(scene->vp.deltah, scene->vp.vh, (float)1 / W);
	scene->vp.vv[x] = 0;
	scene->vp.vv[y] = -scene->vp.v_height;
	scene->vp.vv[z] = 0;
	vec3_scalef(scene->vp.deltav, scene->vp.vv, (float)1 / H);
	scene->vp.vul[x] = scene->cam.o[x] - (scene->vp.vh[x] / 2) - (scene->vp.vv[x] / 2);
	scene->vp.vul[y] = scene->cam.o[y] - (scene->vp.vh[y] / 2) - (scene->vp.vv[y] / 2);
	scene->vp.vul[z] = scene->cam.o[z] - scene->vp.fl - (scene->vp.vh[z] / 2) - (scene->vp.vv[z] / 2);
	scene->vp.pixel00l[x] = scene->vp.vul[x] + (0.5 * (scene->vp.deltah[x] + scene->vp.deltav[x]));
	scene->vp.pixel00l[y] = scene->vp.vul[y] + (0.5 * (scene->vp.deltah[y] + scene->vp.deltav[y]));
	scene->vp.pixel00l[z] = scene->vp.vul[z] + (0.5 * (scene->vp.deltah[z] + scene->vp.deltav[z]));
}

// General parsing function for a camera that sets the information for its
// origin point, a 3D normalized vector, and its fov that should be in the
// interval of [0, 180]
// It also checks if a camera was already found and parsed in the given file
// since each file should only have at most one camera element
int	parse_cam(t_scene *scene, char *line)
{
	if (scene->cam.has_cam)
		return (ft_dprintf(2, MULTIPLE_CAMERAS), 0);
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&scene->cam.o, line, 0))
		return (ft_dprintf(2, CAMERA_USAGE), 0);
	skip_info(&line);
	if (!parse_point(&scene->cam.nv, line, 1))
		return (ft_dprintf(2, CAMERA_USAGE), 0);
	skip_info(&line);
	scene->cam.fov = ft_atoi(line);
	if (!in_range((float)scene->cam.fov, (float)FOV_MIN, (float)FOV_MAX))
		return (ft_dprintf(2, FOV_ERROR), 0);
	//scene->cam.vup[x] = 0;
	//scene->cam.vup[y] = 1;
	//scene->cam.vup[z] = 0;
	//vec3_subf(scene->cam.w, scene->cam.o, scene->cam.nv);
	//vec3_normalizef(scene->cam.w);
	//vec3_crossf(scene->cam.u, scene->cam.vup, scene->cam.w);
	//vec3_normalizef(scene->cam.u);
	//vec3_crossf(scene->cam.v, scene->cam.w, scene->cam.u);
	scene->cam.has_cam = 1;
	return (1);
}

// General parsing function for the ambient light that sets the information
// for its brithness that should be in the interval of [0.0, 1.0] and its color
// It also checks if an ambient light was already found and parsed in the given
// file since each file should only have at most one ambient light element
int	parse_ambience(t_scene *scene, char *line)
{
	if (scene->amb.has_al)
		return (ft_dprintf(2, MULTIPLE_AMBIENCE), 0);
	while (*line && !ft_isdigit(*line) && *line != '-')
		line++;
	if (!(*line))
		return (ft_dprintf(2, AMBIENCE_USAGE), 0);
	scene->amb.al_br = ft_atof(line);
	if (!in_range(scene->amb.al_br, BR_MIN, BR_MAX))
		return (ft_dprintf(2, AMBIENCE_USAGE), 0);
	skip_info(&line);
	if (!(*line))
		return (ft_dprintf(2, AMBIENCE_USAGE), 0);
	if (!parse_color(&scene->amb.al_c, line))
		return (ft_dprintf(2, AMBIENCE_USAGE), 0);
	scene->amb.has_al = 1;
	return (1);
}

// General parsing function for the light that sets the information
// for its origine, its brithness that should be in the interval
// of [0.0, 1.0] and its color as well as adding it to the back of
// the light list since the structure of the program is already
// prepared to receive multiple lights in the same given file
int	parse_light(t_scene *scene, char *line)
{
	t_list	*new_l;
	t_light	*content;

	new_l = new_light();
	if (!new_l)
		return (ft_dprintf(2, NO_SPACE), 0);
	content = light_content(new_l);
	while (!ft_isdigit(*line) && *line != '-')
		line++;
	if (!parse_point(&content->f.sp.c, line, 0))
		return (ft_dprintf(2, LIGHT_USAGE), free(content), free(new_l), 0);
	skip_info(&line);
	content->br = ft_atof(line);
	if (!in_range(content->br, BR_MIN, BR_MAX))
		return (ft_dprintf(2, LIGHT_USAGE), 0);
	skip_info(&line);
	if (!parse_color(&content->c, line))
		return (ft_dprintf(2, LIGHT_USAGE), free(content), free(new_l), 0);
	//new_l->type = L_SP;
	//vec3_copyf(new_l->f.sp.c, new_l->o);
	content->f.sp.r = 1;
	new_l->next = NULL;
	ft_lstadd_back(&scene->lights, new_l);
	return (1);
}
