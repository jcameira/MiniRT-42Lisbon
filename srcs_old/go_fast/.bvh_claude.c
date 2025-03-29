/*
I'll help you translate the BVH (Bounding Volume Hierarchy) and AABB (Axis-Aligned Bounding Box) from C++ to C. This is a non-trivial translation since we'll need to replicate some C++ features in C. Let me break this down into manageable parts.



```c
// Forward declarations for types we'll need
typedef struct vec3 vec3;
typedef struct point3 point3;
typedef struct ray ray;
typedef struct material material;
typedef struct hit_record hit_record;
typedef struct hittable hittable;

// Interval structure to replace C++ interval class
typedef struct interval {
    double min;
    double max;
} interval;

// Constants to replace C++ static members
static const interval INTERVAL_EMPTY = {INFINITY, -INFINITY};
static const interval INTERVAL_UNIVERSE = {-INFINITY, INFINITY};

// Interval helper functions
interval interval_new(double min, double max) {
    interval i = {min, max};
    return i;
}

interval interval_from_intervals(interval a, interval b) {
    return interval_new(fmin(a.min, b.min), fmax(a.max, b.max));
}

bool interval_contains(interval i, double x) {
    return i.min <= x && x <= i.max;
}

bool interval_surrounds(interval i, double x) {
    return i.min < x && x < i.max;
}

double interval_size(interval i) {
    return i.max - i.min;
}

interval interval_expand(interval i, double delta) {
    double padding = delta / 2.0;
    return interval_new(i.min - padding, i.max + padding);
}

// AABB structure to replace C++ aabb class
typedef struct aabb {
    interval x, y, z;
} aabb;

// AABB helper functions
aabb aabb_new(interval x, interval y, interval z) {
    aabb box = {x, y, z};
    // Pad to minimums (equivalent to C++ pad_to_minimums())
    double delta = 0.0001;
    if (interval_size(box.x) < delta) box.x = interval_expand(box.x, delta);
    if (interval_size(box.y) < delta) box.y = interval_expand(box.y, delta);
    if (interval_size(box.z) < delta) box.z = interval_expand(box.z, delta);
    return box;
}

aabb aabb_from_points(point3 a, point3 b) {
    // Assuming point3 has x, y, z members
    interval x = interval_new(fmin(a.x, b.x), fmax(a.x, b.x));
    interval y = interval_new(fmin(a.y, b.y), fmax(a.y, b.y));
    interval z = interval_new(fmin(a.z, b.z), fmax(a.z, b.z));
    return aabb_new(x, y, z);
}

aabb aabb_from_boxes(aabb box0, aabb box1) {
    interval x = interval_from_intervals(box0.x, box1.x);
    interval y = interval_from_intervals(box0.y, box1.y);
    interval z = interval_from_intervals(box0.z, box1.z);
    return aabb_new(x, y, z);
}

interval aabb_axis_interval(aabb* box, int n) {
    if (n == 1) return box->y;
    if (n == 2) return box->z;
    return box->x;
}

bool aabb_hit(aabb* box, ray* r, interval ray_t) {
    // Assuming ray has origin() and direction() methods equivalent
    // We'll need to implement these as functions in C
    for (int axis = 0; axis < 3; axis++) {
        interval ax = aabb_axis_interval(box, axis);
        double ray_orig = ray_origin_component(r, axis);
        double ray_dir = ray_direction_component(r, axis);

        double adinv = 1.0 / ray_dir;
        double t0 = (ax.min - ray_orig) * adinv;
        double t1 = (ax.max - ray_orig) * adinv;

        if (adinv < 0.0) {
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        ray_t.min = t0 > ray_t.min ? t0 : ray_t.min;
        ray_t.max = t1 < ray_t.max ? t1 : ray_t.max;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}

int aabb_longest_axis(aabb* box) {
    double x_size = interval_size(box->x);
    double y_size = interval_size(box->y);
    double z_size = interval_size(box->z);

    if (x_size > y_size)
        return x_size > z_size ? 0 : 2;
    else
        return y_size > z_size ? 1 : 2;
}

// BVH node structure to replace C++ bvh_node class
typedef struct bvh_node {
    hittable* left;
    hittable* right;
    aabb bbox;
} bvh_node;

// Comparison functions for sorting
int box_compare(hittable* a, hittable* b, int axis_index) {
    aabb box_a = hittable_bounding_box(a);
    aabb box_b = hittable_bounding_box(b);

    interval a_interval = aabb_axis_interval(&box_a, axis_index);
    interval b_interval = aabb_axis_interval(&box_b, axis_index);

    return a_interval.min < b_interval.min ? -1 : 1;
}

int box_x_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 0);
}

int box_y_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 1);
}

int box_z_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 2);
}

// BVH creation function (replaces C++ constructor)
bvh_node* bvh_node_create(hittable** objects, size_t start, size_t end) {
    bvh_node* node = malloc(sizeof(bvh_node));

    // Initialize bounding box
    node->bbox = aabb_new(INTERVAL_EMPTY, INTERVAL_EMPTY, INTERVAL_EMPTY);
    for (size_t i = start; i < end; i++) {
        node->bbox = aabb_from_boxes(node->bbox, hittable_bounding_box(objects[i]));
    }

    int axis = aabb_longest_axis(&node->bbox);
    int (*comparator)(const void*, const void*) =
        (axis == 0) ? box_x_compare :
        (axis == 1) ? box_y_compare :
                      box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        node->left = node->right = objects[start];
    } else if (object_span == 2) {
        node->left = objects[start];
        node->right = objects[start + 1];
    } else {
        qsort(objects + start, object_span, sizeof(hittable*), comparator);

        size_t mid = start + object_span/2;
        node->left = (hittable*)bvh_node_create(objects, start, mid);
        node->right = (hittable*)bvh_node_create(objects, mid, end);
    }

    return node;
}

// BVH hit function
bool bvh_node_hit(bvh_node* node, ray* r, interval ray_t, hit_record* rec) {
    if (!aabb_hit(&node->bbox, r, ray_t))
        return false;

    bool hit_left = hittable_hit(node->left, r, ray_t, rec);
    interval right_ray_t = interval_new(ray_t.min, hit_left ? rec->t : ray_t.max);
    bool hit_right = hittable_hit(node->right, r, right_ray_t, rec);

    return hit_left || hit_right;
}

// Cleanup function (C++ destructor equivalent)
void bvh_node_destroy(bvh_node* node) {
    // Only free the node itself if it's a leaf node
    // Otherwise, recursively free the children first
    if (node->left == node->right) {
        free(node);
        return;
    }

    bvh_node_destroy((bvh_node*)node->left);
    bvh_node_destroy((bvh_node*)node->right);
    free(node);
}

```

Let me explain the key changes and decisions made in this translation:

1. C++ Classes to C Structures:
   - Converted the C++ classes to C structures
   - Added separate functions to replace class methods
   - Used naming conventions like `aabb_hit()` instead of member functions

2. Memory Management:
   - Added explicit memory allocation with `malloc()`
   - Added a destroy function for cleanup
   - Carefully managed ownership of child nodes in the BVH

3. Polymorphism Replacement:
   - The C++ code uses inheritance for hittable objects
   - In C, we'll need to implement this using function pointers or a type enum with a union (not shown in this basic translation)

4. Support Types:
   - Added forward declarations for types like vec3, ray, etc.
   - Created an interval structure to replace the C++ interval class
   - Added helper functions for intervals

5. Static Members:
   - Replaced C++ static members with global constants
   - Used const variables for special values like EMPTY and UNIVERSE

Would you like me to explain any specific part in more detail or add any additional functionality? For example, I could:

1. Add the complete hittable interface implementation
2. Show how to handle the polymorphic behavior of different shapes
3. Add more memory safety features
4. Add error handling
5. Include example usage code
*/

// Forward declarations for types we'll need
typedef struct vec3 vec3;
typedef struct point3 point3;
typedef struct ray ray;
typedef struct material material;
typedef struct hit_record hit_record;
typedef struct hittable hittable;

// Interval structure to replace C++ interval class
typedef struct interval {
    double min;
    double max;
} interval;

// Constants to replace C++ static members
static const interval INTERVAL_EMPTY = {INFINITY, -INFINITY};
static const interval INTERVAL_UNIVERSE = {-INFINITY, INFINITY};

// Interval helper functions
interval interval_new(double min, double max) {
    interval i = {min, max};
    return i;
}

interval interval_from_intervals(interval a, interval b) {
    return interval_new(fmin(a.min, b.min), fmax(a.max, b.max));
}

bool interval_contains(interval i, double x) {
    return i.min <= x && x <= i.max;
}

bool interval_surrounds(interval i, double x) {
    return i.min < x && x < i.max;
}

double interval_size(interval i) {
    return i.max - i.min;
}

interval interval_expand(interval i, double delta) {
    double padding = delta / 2.0;
    return interval_new(i.min - padding, i.max + padding);
}

// AABB structure to replace C++ aabb class
typedef struct aabb {
    interval x, y, z;
} aabb;

// AABB helper functions
aabb aabb_new(interval x, interval y, interval z) {
    aabb box = {x, y, z};
    // Pad to minimums (equivalent to C++ pad_to_minimums())
    double delta = 0.0001;
    if (interval_size(box.x) < delta) box.x = interval_expand(box.x, delta);
    if (interval_size(box.y) < delta) box.y = interval_expand(box.y, delta);
    if (interval_size(box.z) < delta) box.z = interval_expand(box.z, delta);
    return box;
}

aabb aabb_from_points(point3 a, point3 b) {
    // Assuming point3 has x, y, z members
    interval x = interval_new(fmin(a.x, b.x), fmax(a.x, b.x));
    interval y = interval_new(fmin(a.y, b.y), fmax(a.y, b.y));
    interval z = interval_new(fmin(a.z, b.z), fmax(a.z, b.z));
    return aabb_new(x, y, z);
}

aabb aabb_from_boxes(aabb box0, aabb box1) {
    interval x = interval_from_intervals(box0.x, box1.x);
    interval y = interval_from_intervals(box0.y, box1.y);
    interval z = interval_from_intervals(box0.z, box1.z);
    return aabb_new(x, y, z);
}

interval aabb_axis_interval(aabb* box, int n) {
    if (n == 1) return box->y;
    if (n == 2) return box->z;
    return box->x;
}

bool aabb_hit(aabb* box, ray* r, interval ray_t) {
    // Assuming ray has origin() and direction() methods equivalent
    // We'll need to implement these as functions in C
    for (int axis = 0; axis < 3; axis++) {
        interval ax = aabb_axis_interval(box, axis);
        double ray_orig = ray_origin_component(r, axis);
        double ray_dir = ray_direction_component(r, axis);

        double adinv = 1.0 / ray_dir;
        double t0 = (ax.min - ray_orig) * adinv;
        double t1 = (ax.max - ray_orig) * adinv;

        if (adinv < 0.0) {
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        ray_t.min = t0 > ray_t.min ? t0 : ray_t.min;
        ray_t.max = t1 < ray_t.max ? t1 : ray_t.max;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}

int aabb_longest_axis(aabb* box) {
    double x_size = interval_size(box->x);
    double y_size = interval_size(box->y);
    double z_size = interval_size(box->z);

    if (x_size > y_size)
        return x_size > z_size ? 0 : 2;
    else
        return y_size > z_size ? 1 : 2;
}

// BVH node structure to replace C++ bvh_node class
typedef struct bvh_node {
    hittable* left;
    hittable* right;
    aabb bbox;
} bvh_node;

// Comparison functions for sorting
int box_compare(hittable* a, hittable* b, int axis_index) {
    aabb box_a = hittable_bounding_box(a);
    aabb box_b = hittable_bounding_box(b);

    interval a_interval = aabb_axis_interval(&box_a, axis_index);
    interval b_interval = aabb_axis_interval(&box_b, axis_index);

    return a_interval.min < b_interval.min ? -1 : 1;
}

int box_x_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 0);
}

int box_y_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 1);
}

int box_z_compare(const void* a, const void* b) {
    return box_compare(*(hittable**)a, *(hittable**)b, 2);
}

// BVH creation function (replaces C++ constructor)
bvh_node* bvh_node_create(hittable** objects, size_t start, size_t end) {
    bvh_node* node = malloc(sizeof(bvh_node));

    // Initialize bounding box
    node->bbox = aabb_new(INTERVAL_EMPTY, INTERVAL_EMPTY, INTERVAL_EMPTY);
    for (size_t i = start; i < end; i++) {
        node->bbox = aabb_from_boxes(node->bbox, hittable_bounding_box(objects[i]));
    }

    int axis = aabb_longest_axis(&node->bbox);
    int (*comparator)(const void*, const void*) =
        (axis == 0) ? box_x_compare :
        (axis == 1) ? box_y_compare :
                      box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        node->left = node->right = objects[start];
    } else if (object_span == 2) {
        node->left = objects[start];
        node->right = objects[start + 1];
    } else {
        qsort(objects + start, object_span, sizeof(hittable*), comparator);

        size_t mid = start + object_span/2;
        node->left = (hittable*)bvh_node_create(objects, start, mid);
        node->right = (hittable*)bvh_node_create(objects, mid, end);
    }

    return node;
}

// BVH hit function
bool bvh_node_hit(bvh_node* node, ray* r, interval ray_t, hit_record* rec) {
    if (!aabb_hit(&node->bbox, r, ray_t))
        return false;

    bool hit_left = hittable_hit(node->left, r, ray_t, rec);
    interval right_ray_t = interval_new(ray_t.min, hit_left ? rec->t : ray_t.max);
    bool hit_right = hittable_hit(node->right, r, right_ray_t, rec);

    return hit_left || hit_right;
}

// Cleanup function (C++ destructor equivalent)
void bvh_node_destroy(bvh_node* node) {
    // Only free the node itself if it's a leaf node
    // Otherwise, recursively free the children first
    if (node->left == node->right) {
        free(node);
        return;
    }

    bvh_node_destroy((bvh_node*)node->left);
    bvh_node_destroy((bvh_node*)node->right);
    free(node);
}
