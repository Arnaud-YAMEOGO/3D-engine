#ifndef TRIANGLE2D_HPP
#define TRIANGLE2D_HPP

#include "Point2D.h"

/**
 * @brief Represents a triangle in 2D space.
 */
class Triangle2D {
public:
    Point2D v1; /**< First vertex */
    Point2D v2;  /**< Second vertex */
    Point2D v3; /**< Third vertex */

    /**
     * @brief Constructor for Triangle2D.
     * @param v1 The first vertex.
     * @param v2 The second vertex.
     * @param v3 The third vertex.
     */
    Triangle2D(const Point2D& v1, const Point2D& v2, const Point2D& v3);
};

#endif