#ifndef QUAD3D_HPP
#define QUAD3D_HPP

#include "Point3D.h"
#include <SDL2/SDL.h>

/**
 * @brief Represents a quadrilateral (quad) in 3D space.
 */
class Quad3D {
public:
    Point3D v1;  /**< First vertex */
    Point3D v2;  /**< Second vertex */
    Point3D v3;  /**< Third vertex */
    Point3D v4;  /**< Fourth vertex */
    SDL_Color color; /**< Color of the quad */

    /**
     * @brief Constructor for Quad3D.
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @param v3 The third vertex.
     * @param v4 The fourth vertex.
     * @param color The color of the quad.
     */
    Quad3D(const Point3D& v1, const Point3D& v2, const Point3D& v3, const Point3D& v4, const SDL_Color& color);
};

#endif