#pragma once

#ifndef COLOR_H
#define COLOR_H


#include "vec3.h"

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_clr) {
    const auto r{ pixel_clr.x() };
    const auto g{ pixel_clr.y() };
    const auto b{ pixel_clr.z() };

    const int rbyte{ static_cast<int>(255.999 * r) };
    const int gbyte{ static_cast<int>(255.999 * g) };
    const int bbyte{ static_cast<int>(255.999 * b) };

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


#endif // !COLOR_H

