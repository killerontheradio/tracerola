#ifndef RTC_H

#include <iostream>
#include "ray.h"
#include "vec3.h"
#include "color.h"

const color black{ 0.0, 0.0, 0.0 };
const color white{ 1.0, 1.0, 1.0 };
const color sky_blue{ 0.3, 0.5, 0.8 };

inline bool hit_sphere(const point3& center, const double radius, const ray& r) {
    const vec3 OC{ center - r.origin() };

    const auto a{ dot(r.direction(), r.direction()) };
    const auto b{ -2 * dot(r.direction(), OC) };
    const auto c{ dot(OC, OC) - radius * radius };

    const auto discriminant{ b * b - 4 * a * c };

    return (discriminant >= 0);
}


#endif // !RTC_H
