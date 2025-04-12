/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bvh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-de <cjoao-de@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:54:46 by cjoao-de          #+#    #+#             */
/*   Updated: 2025/04/12 16:25:54 by cjoao-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct {
	float min;
	float max;
} Interval;

typedef struct {
	Interval x;
	Interval y;
	Interval z;
} AABB;

// typedef struct Ray {
// 	double origin[3];
// 	double direction[3];
// } Ray;

// typedef struct HitRecord {
// 	double t;
// 	double point[3];	p[3]
// 	double normal[3];
// 	int front_face;
// } HitRecord;

// Abstract hittable interface with function pointers
typedef struct Hittable {
	void *object; // Generic pointer to the actual object (sphere, BVH node, etc.)
	int (*hit)(void *object, const t_ray *ray, double t_min, double t_max, t_hitrecord *rec);
	AABB (*bounding_box)(void *object);
} Hittable;


typedef struct BVHNode {
	Hittable left;
	Hittable right;
	AABB box;
} BVHNode;
