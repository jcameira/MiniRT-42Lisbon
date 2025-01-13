/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:43:45 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/01/13 01:13:07 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// 2. AABB Operations
int aabb_hit(const AABB *box, const t_ray *ray, float t_min, float t_max) {
	for (int i = 0; i < 3; i++) {
		float invD = 1.0 / ray->dir[i];
		float t0 = (box->x.min - ray->o[i]) * invD;
		float t1 = (box->x.max - ray->o[i]) * invD;
		if (invD < 0.0) {
			float temp = t0;
			t0 = t1;
			t1 = temp;
		}
		t_min = fmax(t0, t_min);
		t_max = fmin(t1, t_max);
		if (t_max <= t_min) return 0;
	}
	return 1;
}

AABB surrounding_box(const AABB *box0, const AABB *box1) {
	return (AABB){
		.x = {.min = fmin(box0->x.min, box1->x.min), .max = fmax(box0->x.max, box1->x.max)},
		.y = {.min = fmin(box0->y.min, box1->y.min), .max = fmax(box0->y.max, box1->y.max)},
		.z = {.min = fmin(box0->z.min, box1->z.min), .max = fmax(box0->z.max, box1->z.max)},
	};
}


// 3. BVH Node


int	bvh_hit(void *object, const t_ray *ray, float t_min, float t_max, t_hitrecord *rec)
{
	BVHNode *node;
	t_hitrecord left_rec;
	t_hitrecord right_rec;
	int hit_left;
	int hit_right;

	node = (BVHNode *)object;
	if (!aabb_hit(&node->box, ray, t_min, t_max))
		return 0;
	hit_left = node->left.hit(node->left.object, ray, t_min, t_max, &left_rec);
	hit_right = node->right.hit(node->right.object, ray, t_min, t_max, &right_rec);
	if (hit_left && hit_right)
	// *rec = (left_rec.t < right_rec.t) ? left_rec : right_rec;
	{
		if (left_rec.t < right_rec.t)
			*rec = left_rec;
		else
			*rec = right_rec;
		return 1;
	}
	else if (hit_left)
	{
		*rec = left_rec;
		return 1;
	}
	else if (hit_right)
	{
		*rec = right_rec;
		return 1;
	}
	return 0;
}

AABB	bvh_bounding_box(void *object)
{
	BVHNode *node;
	node = (BVHNode *)object;
	return (node->box);
}


// 4. BVH Construction
BVHNode	*create_bvh(Hittable *objects, int start, int end)
{
	BVHNode	*node;
	AABB	left_box;
	AABB	right_box;
	int		mid;

	node = malloc(sizeof(BVHNode));

	// Sort objects by bounding box centroid (e.g., along the x-axis)
	// Sorting logic would go here. Skipping for simplicity.

	if (end - start == 1)
	{
		node->left = objects[start];
		node->right = objects[start];
	}
	else if (end - start == 2)
	{
		node->left = objects[start];
		node->right = objects[start + 1];
	}
	else
	{
		mid = start + (end - start) / 2;
		node->left = (Hittable){.object = create_bvh(objects, start, mid),
								.hit = bvh_hit, .bounding_box = bvh_bounding_box};
		node->right = (Hittable){.object = create_bvh(objects, mid, end),
									.hit = bvh_hit, .bounding_box = bvh_bounding_box};
	}
	left_box = node->left.bounding_box(node->left.object);
	right_box = node->right.bounding_box(node->right.object);
	node->box = surrounding_box(&left_box, &right_box);
	return (node);
}
