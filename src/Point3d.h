#ifndef POINT3D_HPP
#define POINT3D_HPP

/**
 * @brief Represents a point in 3D space.
 */
class Point3D {
public:
    float x; /**< x coordinate */
    float y; /**< y coordinate */
    float z; /**< z coordinate */

     /**
     * @brief Default constructor.
     * @param x The x coordinate. Default value is 0.0f.
     * @param y The y coordinate. Default value is 0.0f.
     * @param z The z coordinate. Default value is 0.0f.
     */
    Point3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
};

#endif