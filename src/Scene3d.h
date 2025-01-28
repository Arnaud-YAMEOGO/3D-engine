#ifndef SCENE3D_HPP
#define SCENE3D_HPP

#include <vector>
#include <SDL2/SDL.h>
#include "Quad3D.h"
#include "Point3D.h"
#include "Triangle3D.h"
#include "Point2D.h"

/**
 * @brief Represents a 3D scene composed of quads.
 */
class Scene3D {
public:
    std::vector<Quad3D> quads;  /**< List of quads in the scene */

    /**
     * @brief Adds a quad to the scene.
     * @param quad The quad to add.
     */
    void addQuad(const Quad3D& quad);

    /**
     * @brief Generates a cube.
     * @return The generated cube.
     */
    Scene3D generateSphere(int slices, int stacks);

    /**
     * @brief Generates a cube.
     * @return The generated cube.
     */
    Scene3D generateCube();

    /**
     * @brief Rotates a 3D point around the X and Y axes.
     * @param p The point to rotate.
     * @param angleX Rotation angle around the X axis (in radians).
     * @param angleY Rotation angle around the Y axis (in radians).
     * @return The rotated point.
     */
    Point3D rotatePoint(const Point3D& p, float angleX, float angleY);

    /**
     * @brief Projects a 3D point onto the 2D screen.
     * @param p The 3D point.
     * @param width The screen width.
     * @param height The screen height.
     * @return The projected 2D point.
     */
    Point2D project(const Point3D& p, int width, int height);

    /**
     * @brief Calculates the average depth of a quad.
     * @param quad The quad to calculate depth from.
     * @return The average depth of the quad.
     */
    float averageDepth(const Quad3D& quad);

    /**
     * @brief Draws a triangle on the screen.
     * @param renderer SDL renderer used for drawing
     * @param tri triangle to draw.
     */
    void drawTriangle(SDL_Renderer* renderer, const Triangle3D& tri);

    /**
     * @brief Draws a filled quadrilateral on the screen.
     * @param renderer SDL renderer used for drawing
     * @param quad quad to draw.
     */
    void drawQuad(SDL_Renderer* renderer, const Quad3D& quad);
};



#endif