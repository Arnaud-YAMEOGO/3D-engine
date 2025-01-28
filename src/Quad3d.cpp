#include "Quad3d.h"

/**
 * @brief Constructor for Quad3D.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @param v3 The third vertex.
 * @param v4 The fourth vertex.
 * @param color The color of the quad.
 */
Quad3D::Quad3D(const Point3D& v1, const Point3D& v2, const Point3D& v3, const Point3D& v4, const SDL_Color& color)
        : v1(v1), v2(v2), v3(v3), v4(v4), color(color) {}