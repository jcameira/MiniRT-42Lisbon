#include "rtweekend.h"
#include "bvh.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"

int main() {
    // Create scene with 3 spheres
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,0), 1.0));
    world.add(make_shared<sphere>(point3(2,0,0), 0.5));
    world.add(make_shared<sphere>(point3(-2,1,0), 0.7));

    // Build BVH from world
    auto root = make_shared<bvh_node>(world);

    // Test ray intersection
    ray r(point3(0,0,-5), vec3(0,0,1));
    hit_record rec;

    if (root->hit(r, interval(0.001, infinity), rec)) {
        std::cout << "Hit at point: "
                  << rec.p.x() << ","
                  << rec.p.y() << ","
                  << rec.p.z() << "\n";
    }

    return 0;
}
