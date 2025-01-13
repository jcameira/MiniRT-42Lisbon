#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

// Basic structures
typedef struct {
    double x[3];
} vec3;

typedef vec3 point3;

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

typedef struct {
    double min;
    double max;
} interval;

typedef struct {
    interval x, y, z;
} aabb;

typedef struct {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
} hit_record;

// Forward declarations
struct hittable;
typedef bool (*hit_fn)(const struct hittable*, const ray*, interval, hit_record*);
typedef aabb (*bbox_fn)(const struct hittable*);

typedef struct hittable {
    void* object;
    hit_fn hit;
    bbox_fn bounding_box;
} hittable;

typedef struct {
    point3 center;
    double radius;
} sphere;

typedef struct bvh_node {
    hittable* left;
    hittable* right;
    aabb bbox;
} bvh_node;

// Vector operations
vec3 vec3_create(double x, double y, double z) {
    vec3 v = {{x, y, z}};
    return v;
}

vec3 vec3_add(vec3 a, vec3 b) {
    return vec3_create(a.x[0] + b.x[0], a.x[1] + b.x[1], a.x[2] + b.x[2]);
}

vec3 vec3_subtract(vec3 a, vec3 b) {
    return vec3_create(a.x[0] - b.x[0], a.x[1] - b.x[1], a.x[2] - b.x[2]);
}

vec3 vec3_multiply(vec3 v, double t) {
    return vec3_create(v.x[0] * t, v.x[1] * t, v.x[2] * t);
}

double vec3_dot(vec3 a, vec3 b) {
    return a.x[0] * b.x[0] + a.x[1] * b.x[1] + a.x[2] * b.x[2];
}

// AABB operations
bool aabb_hit(const aabb* box, const ray* r, interval ray_t) {
    for (int a = 0; a < 3; a++) {
        // interval* axis = (a == 0) ? &box->x : (a == 1) ? &box->y : &box->z;
		double axis_min = (a == 0) ? box->x.min : (a == 1) ? box->y.min : box->z.min;
        double axis_max = (a == 0) ? box->x.max : (a == 1) ? box->y.max : box->z.max;
        double origin = r->orig.x[a];
        double direction = r->dir.x[a];

        double inv_d = 1.0f / direction;
        double t0 = (axis_min - origin) * inv_d;
        double t1 = (axis_max - origin) * inv_d;

        if (inv_d < 0.0f) {
            double tmp = t0;
            t0 = t1;
            t1 = tmp;
        }

        ray_t.min = t0 > ray_t.min ? t0 : ray_t.min;
        ray_t.max = t1 < ray_t.max ? t1 : ray_t.max;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}

// Sphere operations
bool sphere_hit(const hittable* h, const ray* r, interval ray_t, hit_record* rec) {
    sphere* s = (sphere*)h->object;
    vec3 oc = vec3_subtract(r->orig, s->center);
    double a = vec3_dot(r->dir, r->dir);
    double half_b = vec3_dot(oc, r->dir);
    double c = vec3_dot(oc, oc) - s->radius * s->radius;

    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;

    double sqrtd = sqrt(discriminant);
    double root = (-half_b - sqrtd) / a;
    if (root < ray_t.min || ray_t.max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < ray_t.min || ray_t.max < root)
            return false;
    }

    rec->t = root;
    rec->p = vec3_add(r->orig, vec3_multiply(r->dir, rec->t));
    vec3 outward_normal = vec3_multiply(vec3_subtract(rec->p, s->center), 1.0/s->radius);
    rec->front_face = vec3_dot(r->dir, outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : vec3_multiply(outward_normal, -1);

    return true;
}

aabb sphere_bbox(const hittable* h) {
    sphere* s = (sphere*)h->object;
    vec3 radius_vec = vec3_create(s->radius, s->radius, s->radius);
    vec3 min = vec3_subtract(s->center, radius_vec);
    vec3 max = vec3_add(s->center, radius_vec);

    aabb box = {
        {min.x[0], max.x[0]},
        {min.x[1], max.x[1]},
        {min.x[2], max.x[2]}
    };
    return box;
}

// BVH operations
bool bvh_hit(const hittable* h, const ray* r, interval ray_t, hit_record* rec) {
    bvh_node* node = (bvh_node*)h->object;

    if (!aabb_hit(&node->bbox, r, ray_t))
        return false;

    bool hit_left = node->left->hit(node->left, r, ray_t, rec);
    interval right_ray_t = {ray_t.min, hit_left ? rec->t : ray_t.max};
    bool hit_right = node->right->hit(node->right, r, right_ray_t, rec);

    return hit_left || hit_right;
}

aabb bvh_bbox(const hittable* h) {
    bvh_node* node = (bvh_node*)h->object;
    return node->bbox;
}

static int current_axis = 0;  // Global for qsort comparison

int compare_boxes(const void* a, const void* b) {
    hittable* ha = *(hittable**)a;
    hittable* hb = *(hittable**)b;
    aabb box_a = ha->bounding_box(ha);
    aabb box_b = hb->bounding_box(hb);

    double min_a = (current_axis == 0) ? box_a.x.min :
                   (current_axis == 1) ? box_a.y.min : box_a.z.min;
    double min_b = (current_axis == 0) ? box_b.x.min :
                   (current_axis == 1) ? box_b.y.min : box_b.z.min;

    if (min_a < min_b) return -1;
    if (min_a > min_b) return 1;
    return 0;
}

// int compare_by_axis(const void* a, const void* b, int axis) {
//     hittable* ha = *(hittable**)a;
//     hittable* hb = *(hittable**)b;
//     aabb box_a = ha->bounding_box(ha);
//     aabb box_b = hb->bounding_box(hb);

//     interval* a_interval = (axis == 0) ? &box_a.x : (axis == 1) ? &box_a.y : &box_a.z;
//     interval* b_interval = (axis == 0) ? &box_b.x : (axis == 1) ? &box_b.y : &box_b.z;

//     if (a_interval->min < b_interval->min) return -1;
//     if (a_interval->min > b_interval->min) return 1;
//     return 0;
// }

hittable* create_bvh_node(hittable** objects, int start, int end) {
    bvh_node* node = malloc(sizeof(bvh_node));
    hittable* h = malloc(sizeof(hittable));

    h->object = node;
    h->hit = bvh_hit;
    h->bounding_box = bvh_bbox;

    // Find bounding box for all objects
    node->bbox = objects[start]->bounding_box(objects[start]);
    for (int i = start + 1; i < end; i++) {
        aabb temp_box = objects[i]->bounding_box(objects[i]);
        node->bbox = (aabb){
            {fmin(node->bbox.x.min, temp_box.x.min), fmax(node->bbox.x.max, temp_box.x.max)},
            {fmin(node->bbox.y.min, temp_box.y.min), fmax(node->bbox.y.max, temp_box.y.max)},
            {fmin(node->bbox.z.min, temp_box.z.min), fmax(node->bbox.z.max, temp_box.z.max)}
        };
    }

    int object_span = end - start;
    if (object_span == 1) {
        node->left = node->right = objects[start];
    } else if (object_span == 2) {
        node->left = objects[start];
        node->right = objects[start + 1];
    } else {
        current_axis = 0;  // Choose axis (can be random or cyclic)
        // qsort(objects + start, object_span, sizeof(hittable*), compare_by_axis, 0);
        qsort(objects + start, object_span, sizeof(hittable*), compare_boxes);
        int mid = start + object_span/2;
        node->left = create_bvh_node(objects, start, mid);
        node->right = create_bvh_node(objects, mid, end);
    }

    return h;
}

int main() {
    // Create spheres
    hittable* objects[3];

    for (int i = 0; i < 3; i++) {
        sphere* s = malloc(sizeof(sphere));
        hittable* h = malloc(sizeof(hittable));

        h->object = s;
        h->hit = sphere_hit;
        h->bounding_box = sphere_bbox;

        objects[i] = h;
    }

    ((sphere*)objects[0]->object)->center = vec3_create(0, 0, 0);
    ((sphere*)objects[0]->object)->radius = 1.0;

    ((sphere*)objects[1]->object)->center = vec3_create(2, 0, 0);
    ((sphere*)objects[1]->object)->radius = 0.5;

    ((sphere*)objects[2]->object)->center = vec3_create(-2, 1, 0);
    ((sphere*)objects[2]->object)->radius = 0.7;

    // Build BVH
    hittable* root = create_bvh_node(objects, 0, 3);

    // Test ray intersection
    ray r = {vec3_create(0,0,-5), vec3_create(0,0,1)};
    hit_record rec;

    if (root->hit(root, &r, (interval){0.001, DBL_MAX}, &rec)) {
        printf("Hit at point: %f,%f,%f\n", rec.p.x[0], rec.p.x[1], rec.p.x[2]);
    }

    // Cleanup
    // Note: Need proper cleanup of all allocated memory

    return 0;
}
