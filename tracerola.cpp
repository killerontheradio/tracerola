#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "rtc.h"

constexpr auto ASPECT_RATIO{ 16.0 / 9.0 };

constexpr int IMG_WIDTH{ 400 };
static int IMG_HEIGHT{ static_cast<int>(IMG_WIDTH / ASPECT_RATIO) };

constexpr auto VIEWP_HEIGHT{ 2.0 };
static double VIEWP_WIDTH{ VIEWP_HEIGHT * (static_cast<double>(IMG_WIDTH) / IMG_HEIGHT) };

static const vec3 viewport_u{ VIEWP_WIDTH, 0, 0 };
static const vec3 viewport_v{ 0, -VIEWP_HEIGHT, 0 };

static const vec3 pixel_delta_u{ viewport_u / IMG_WIDTH };
static const vec3 pixel_delta_v{ viewport_v / IMG_HEIGHT };

constexpr auto focal_length{ 1.0 };
static const point3 camera_center{ 0, 0, 0 };

static vec3 viewport_upper_left{ camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2) };

// the centre of the (0, 0) pixel
static const auto pixel00_loc{ viewport_upper_left + (0.5 * (pixel_delta_u + pixel_delta_v)) };


inline color ray_color(const ray& r) {
    if (hit_sphere(point3(0, 0, -1), 0.2, r)) {
        return color(1, 0, 0);
    }
    const vec3 unit_direction{ unit_vector(r.direction()) };
    const double a{ 0.5 * (unit_direction.y() + 1) };
    return color{ (1 - a) * white + a * sky_blue };
}

/*
 * MAIN
 */
int main() {
    IMG_HEIGHT = (IMG_HEIGHT < 1) ? 1 : IMG_HEIGHT;

    // Formatting information; ESSENTIAL
    std::cout << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

    for (int j = 0; j < IMG_HEIGHT; ++j) {
        for (int i = 0; i < IMG_WIDTH; ++i) {

            auto pixel_center{ pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v) };

            auto ray_direction = pixel_center - camera_center;

            ray r{ camera_center, ray_direction };

            auto pixel_clr{ ray_color(r) };

            write_color(std::cout, pixel_clr);
        }
    }
    std::clog << "Done.\n";
}