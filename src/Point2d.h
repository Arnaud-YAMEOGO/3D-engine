#ifndef POINT2D_HPP
#define POINT2D_HPP

/**
 * @brief Represents a point in 2D space.
 */
class Point2D {
public:
    int x; /**< x coordinate */
    int y;  /**< y coordinate */
     /**
     * @brief Constructor for Point2D.
     * @param x The x coordinate. Default value is 0.
     * @param y The y coordinate. Default value is 0.
     */
    Point2D(int x = 0, int y = 0);
};

#endif