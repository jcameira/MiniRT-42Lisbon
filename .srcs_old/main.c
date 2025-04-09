/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:39:56 by jcameira          #+#    #+#             */
/*   Updated: 2025/03/12 13:43:45 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// t_coord project_normalized_vec3(const vec3 vec)
// {
// 	t_coord pos;

// 	// Convert from [-1,1] to  [0,W-1] and [0,H-1]
// 	pos.pos[x] = (int)((vec[x] + 1.0f) * (W / 2));
// 	pos.pos[y] = (int)((1.0f - vec[y]) * (H / 2));

// 	// Clamp to viewport bounds
// 	pos.pos[x] = clamp(pos.pos[x], 0, W - 1);
// 	pos.pos[y] = clamp(pos.pos[y], 0, H - 1);
// 	// pos[x] = (pos[x] < 0) ? 0 : ((pos[x] >= W) ? W - 1 : pos[x]);
// 	// pos[y] = (pos[y] < 0) ? 0 : ((pos[y] >= H) ? H - 1 : pos[y]);
// 	return pos;
// }



int	render_rayt(t_minirt *s)
{
	t_pixel	pixel_color;
	t_pixel	temp_color;
    float	pixel_center[3];
    float	ray_direction[3];

	for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
			ft_bzero(&pixel_color, sizeof(pixel_color));
			for (int sample = 0; sample < RAYS_PER_PIXEL; sample++){
				pixel_center[x] = s->cam.vp.pixel00l[x] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[x]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[x]);
				pixel_center[y] = s->cam.vp.pixel00l[y] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[y]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[y]);
				pixel_center[z] = s->cam.vp.pixel00l[z] + ((i + (random_float() - 0.5)) * s->cam.vp.deltah[z]) + ((j + (random_float() - 0.5)) * s->cam.vp.deltav[z]);
				//pixel_center[x] = s->cam.vp.pixel00l[x] + (i * s->cam.vp.deltah[x]) + (j * s->cam.vp.deltav[x]);
				//pixel_center[y] = s->cam.vp.pixel00l[y] + (i * s->cam.vp.deltah[y]) + (j * s->cam.vp.deltav[y]);
				//pixel_center[z] = s->cam.vp.pixel00l[z] + (i * s->cam.vp.deltah[z]) + (j * s->cam.vp.deltav[z]);
				vec3_subf(ray_direction, pixel_center, s->cam.o);
				temp_color = ray_color(s, get_ray(s->cam.o, ray_direction), 50);
				add_pixel_color(&pixel_color, temp_color);
			}
			anti_aliasing_get_color(&pixel_color);
			gamma_correction(&pixel_color);
			pixel_put(&s->cam.img, i, j, pixel_color.rgb);
		}
	}
	s->menu.click_spam = false;
	mlx_put_image_to_window(s->mlx, s->win_rayt, s->cam.img.image, 0, 0);
	return (0);
}

int	minirt(t_minirt *s)
{
	render_rayt(s);
	render_menu(s);
	return (0);
}

void	setup_minirt(t_scene scene, t_camera cam)
{
	setup_mlx(scene);
}

int	fill_hittable_array(t_scene *scene)
{
	t_figure	*temp_f;
	t_light		*temp_l;
	int			i;

	scene->obj_nbr = ft_lstsize((t_list *)scene->figures) + ft_lstsize((t_list *)scene->lights);
	printf("Object_number -> %d\n", scene->obj_nbr);
	scene->objects = malloc(sizeof(void *) * scene->obj_nbr);
	if (!scene->objects)
		return (0);
	i = -1;
	temp_f = scene->figures;
	while (temp_f)
	{
		scene->objects[++i] = temp_f;
		temp_f = temp_f->next;
	}
	temp_l = scene->lights;
	while (temp_l)
	{
		scene->objects[++i] = temp_l;
		temp_l = temp_l->next;
	}
	return (1);
}

t_bvh	*new_bvh_node(void)
{
	t_bvh	*new;

	new = malloc(sizeof(t_bvh));
	if (!new)
		return (ft_dprintf(2, NO_SPACE), NULL);
	new->figure = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	bvh_sort(void ***objects, int start, int end, int axis)
{
	void	*temp_o;
	float	temp_b[3][2];
	int		i;
	int		j;

	i = start - 1;
	while (++i < end - 1)
	{
		j = i;
		while (++j < end)
		{
			vec2_copyf(temp_b[x], ((t_figure *)(*objects)[j])->b.x_interval);
			vec2_copyf(temp_b[y], ((t_figure *)(*objects)[j])->b.y_interval);
			vec2_copyf(temp_b[z], ((t_figure *)(*objects)[j])->b.z_interval);
			if (temp_b[axis][min] < temp_b[axis][min])
			{
				temp_o = (*objects)[i];
				(*objects)[i] = (*objects)[j];
				(*objects)[j] = temp_o;
				i = start - 1;
				break ;
			}
		}
	}
}

void	unite_interval(float *dest, float *interval1, float *interval2)
{
	if (interval1[min] <= interval2[min])
		dest[min] = interval1[min];
	else
		dest[min] = interval2[min];
	if (interval1[max] >= interval2[max])
		dest[max] = interval1[max];
	else
		dest[max] = interval2[max];
}

t_bbox	bvh_bbox(t_bvh *left, t_bvh *right)
{
	t_bbox	new_bbox;

	if (left && right)
	{
		unite_interval(new_bbox.x_interval, left->b.x_interval, right->b.x_interval);
		unite_interval(new_bbox.y_interval, left->b.y_interval, right->b.y_interval);
		unite_interval(new_bbox.z_interval, left->b.z_interval, right->b.z_interval);
	}
	else if (left)
		return (left->b);
	else
		return (right->b);
	return (new_bbox);
}

void	copy_bbox(t_bbox *dest, t_bbox *src)
{
	dest->x_interval[min] = src->x_interval[min];
	dest->x_interval[max] = src->x_interval[max];
	dest->y_interval[min] = src->y_interval[min];
	dest->y_interval[max] = src->y_interval[max];
	dest->z_interval[min] = src->z_interval[min];
	dest->z_interval[max] = src->z_interval[max];
}

t_bvh	*bvh_tree(t_scene *scene, t_bvh *bvh, int start, int end)
{
	int	span;
	int	mid;
	int	random;

	if (start >= scene->obj_nbr)
		return (NULL);
	//printf("Start -> %d\n", start);
	bvh = new_bvh_node();
	if (!bvh)
		return (NULL);
	bvh->is_light = 0;
	random = random_int_in_interval(0, 2);
	span = end - start;
	if (!span)
	{
		bvh->figure = scene->objects[start];
		//copy_bbox(&(bvh->b), &(((t_figure*)bvh->figure)->b));
		bvh->b = ((t_figure*)bvh->figure)->b;
		bvh->type = ((t_figure*)bvh->figure)->type;
		//printf("Element Type -> %d\n", bvh->type);
		if (bvh->type == L_QU || bvh->type == L_SP)
			bvh->is_light = 1;
		return (bvh);
	}
	bvh_sort(&scene->objects, start, end, random);
	mid = start + (span / 2);
	//printf("Mid -> %d\n", mid);
	bvh->left = bvh_tree(scene, bvh->left, start, mid);
	bvh->right = bvh_tree(scene, bvh->right, mid + 1, end);
	//if (bvh->left && bvh->right)
	//	bvh->b = bvh_bbox(bvh->left->b, bvh->right->b);
	bvh->b = bvh_bbox(bvh->left, bvh->right);
	bvh->type = NOT_AN_OBJECT;
	return (bvh);
}

void	print_bvh_type(t_bvh *bvh)
{
	static int i;

	if (!bvh)
		return ;
	printf("Node -> %d\n", i++);
	print_bvh_type(bvh->left);
	if (!bvh->left && !bvh->right)
		printf("Element type -> %d, is light -> %d\n", bvh->type, bvh->is_light);
	print_bvh_type(bvh->right);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	cam;

	if (argc != 2)
		return (ft_dprintf(2, NO_ARGS), 1);
	if (!ft_strnstr(argv[y], ".rt", ft_strlen(argv[y]))
		|| *(ft_strnstr(argv[y], ".rt", ft_strlen(argv[y])) + 3))
		return (ft_dprintf(2, INVALID_RT), 1);
	ft_bzero((void *)&scene, sizeof(scene));
	ft_bzero((void *)&cam, sizeof(cam));
	if (!parser(&scene, &cam, argv[y])
		|| !check_needed_elements(cam, scene, argv[y]))
		return (free_scene(&scene), 1);
	if (!fill_hittable_array(&scene))
		return (ft_dprintf(2, NO_SPACE), 1);
	int i = -1;
	while (++i < scene.obj_nbr)
		printf("Object type -> %d\n", ((t_figure *)scene.objects[i])->type);
	print_parsed_elements(cam, scene);
	scene.bvh = bvh_tree(&scene, scene.bvh, 0, scene.obj_nbr - 1);
	if (!scene.bvh)
		return (ft_dprintf(2, NO_SPACE), 1);
	print_bvh_type(scene.bvh);
	setup_minirt(scene, cam);
	return (0);
}
