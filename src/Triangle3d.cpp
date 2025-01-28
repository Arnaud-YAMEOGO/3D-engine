#include "Triangle3d.h"


/**
 * @brief Constructor for Triangle3D.
 * @param v1 The first vertex.
 * @param v2 The second vertex.
 * @param v3 The third vertex.
 * @param color The color of the triangle.
 */
Triangle3D::Triangle3D(const Point3D& v1, const Point3D& v2, const Point3D& v3, const SDL_Color& color)
        : v1(v1), v2(v2), v3(v3), color(color) {}