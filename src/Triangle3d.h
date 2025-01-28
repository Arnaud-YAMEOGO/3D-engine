#ifndef TRIANGLE3D_HPP
#define TRIANGLE3D_HPP

#include "Point3D.h"
#include <SDL2/SDL.h>

/**
 * @brief Represents a triangle in 3D space.
 */
class Triangle3D {
public:
    Point3D v1;  /**< First vertex */
    Point3D v2;  /**< Second vertex */
    Point3D v3;  /**< Third vertex */
    SDL_Color color; /**< Color of the triangle */

    /**
     * @brief Constructor for Triangle3D.
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @param v3 The third vertex.
     * @param color The color of the triangle.
     */
    Triangle3D(const Point3D& v1, const Point3D& v2, const Point3D& v3, const SDL_Color& color);
};

#endif