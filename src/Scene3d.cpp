#include <cmath>
#include "Scene3d.h"

// Dimensions de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

// Variables globales pour la rotation
float rotationX = 0.0f;
float rotationY = 0.0f;

// Variables globales pour la translation
float translationX = 0.0f;
float translationY = 0.0f;
float translationZ = 0.0f;


/**
 * @brief Adds a quad to the scene.
 * @param quad The quad to add.
 */
void Scene3D::addQuad(const Quad3D& quad) {
        quads.push_back(quad);
}

/**
 * @brief Generates a sphere scene.
 * @param slices The number of slices.
 * @param stacks The number of stacks.
 * @return The sphere scene.
 */
Scene3D Scene3D::generateSphere(int slices, int stacks) {
    Scene3D scene;
    for (int i = 0; i < stacks; ++i) {
        float lat0 = M_PI * (-0.5 + static_cast<float>(i) / stacks);
        float lat1 = M_PI * (-0.5 + static_cast<float>(i + 1) / stacks);

        for (int j = 0; j < slices; ++j) {
            float lon0 = 2 * M_PI * static_cast<float>(j) / slices;
            float lon1 = 2 * M_PI * static_cast<float>(j + 1) / slices;

            Point3D v1 = {cos(lat0) * cos(lon0), sin(lat0), cos(lat0) * sin(lon0)};
            Point3D v2 = {cos(lat1) * cos(lon0), sin(lat1), cos(lat1) * sin(lon0)};
            Point3D v3 = {cos(lat1) * cos(lon1), sin(lat1), cos(lat1) * sin(lon1)};
            Point3D v4 = {cos(lat0) * cos(lon1), sin(lat0), cos(lat0) * sin(lon1)};

            SDL_Color color = {static_cast<Uint8>(255 * (j % 2)), static_cast<Uint8>(255 * (i % 2)), 255, 255};
             scene.addQuad(Quad3D(v1, v2, v3, v4, color));
        }
    }
    return scene;
}

/**
 * @brief Generates a cube scene.
 * @return The cube scene.
 */
Scene3D Scene3D::generateCube() {
    std::vector<Point3D> vertices = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, // Face arrière
        {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}  // Face avant
    };

    Scene3D scene;
    scene.addQuad(Quad3D(vertices[0], vertices[1], vertices[2], vertices[3], {255, 0, 0, 255})); // Arrière
    scene.addQuad(Quad3D(vertices[4], vertices[5], vertices[6], vertices[7], {0, 255, 0, 255})); // Avant
    scene.addQuad(Quad3D(vertices[0], vertices[1], vertices[5], vertices[4], {0, 0, 255, 255})); // Bas
    scene.addQuad(Quad3D(vertices[3], vertices[2], vertices[6], vertices[7], {255, 255, 0, 255})); // Haut
    scene.addQuad(Quad3D(vertices[0], vertices[3], vertices[7], vertices[4], {0, 255, 255, 255})); // Gauche
    scene.addQuad(Quad3D(vertices[1], vertices[2], vertices[6], vertices[5], {255, 0, 255, 255})); // Droite

    return scene;
}


/**
 * @brief Rotates a 3D point around the X and Y axes.
 * @param p The point to rotate.
 * @param angleX Rotation angle around the X axis (in radians).
 * @param angleY Rotation angle around the Y axis (in radians).
 * @return The rotated point.
 */
Point3D Scene3D::rotatePoint(const Point3D& p, float angleX, float angleY) {
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float y = cosX * p.y - sinX * p.z;
    float z = sinX * p.y + cosX * p.z;

    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float x = cosY * p.x + sinY * z;
    z = -sinY * p.x + cosY * z;

    return {x, y, z};
}


/**
 * @brief Projects a 3D point onto the 2D screen.
 * @param p The 3D point.
 * @param width The screen width.
 * @param height The screen height.
 * @return The projected 2D point.
 */
Point2D Scene3D::project(const Point3D& p, int width, int height) {
    float scale = 300.0f / (p.z + 4.0f);
    int x = static_cast<int>(p.x * scale + width / 2);
    int y = static_cast<int>(-p.y * scale + height / 2);
    return {x, y};
}

/**
 * @brief Calculates the average depth of a quad.
 * @param quad The quad to calculate depth from.
 * @return The average depth of the quad.
 */
float Scene3D::averageDepth(const Quad3D& quad) {
    return (quad.v1.z + quad.v2.z + quad.v3.z + quad.v4.z) / 4.0f;
}

/**
 * @brief Draws a triangle on the screen.
 * @param renderer SDL renderer used for drawing
 * @param tri triangle to draw.
 */
void Scene3D::drawTriangle(SDL_Renderer* renderer, const Triangle3D& tri) {
    Point2D p1 = project(tri.v1, WIDTH, HEIGHT);
    Point2D p2 = project(tri.v2, WIDTH, HEIGHT);
    Point2D p3 = project(tri.v3, WIDTH, HEIGHT);

    SDL_SetRenderDrawColor(renderer, tri.color.r, tri.color.g, tri.color.b, 255);
    SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
    SDL_RenderDrawLine(renderer, p2.x, p2.y, p3.x, p3.y);
    SDL_RenderDrawLine(renderer, p3.x, p3.y, p1.x, p1.y);
}

/**
 * @brief Draws a filled quadrilateral on the screen.
 * @param renderer SDL renderer used for drawing
 * @param quad quad to draw.
 */
void Scene3D::drawQuad(SDL_Renderer* renderer, const Quad3D& quad) {
    Point2D points[4];
    Point3D transformedV[4];

    transformedV[0] = quad.v1;
    transformedV[1] = quad.v2;
    transformedV[2] = quad.v3;
    transformedV[3] = quad.v4;

    // Application de la translation
    for (int i =0; i < 4; i++){
         transformedV[i].x += translationX;
         transformedV[i].y += translationY;
         transformedV[i].z += translationZ;
    }

     for (int i =0; i < 4; i++){
          points[i] = project(transformedV[i], WIDTH, HEIGHT);
     }

    float xy[8];
    for(int i = 0; i < 4; ++i) {
        xy[i*2] = points[i].x;
        xy[i*2 + 1] = points[i].y;
    }

    SDL_Color colors[4];
    for (int i = 0; i < 4; ++i) {
        colors[i].r = quad.color.r;
        colors[i].g = quad.color.g;
        colors[i].b = quad.color.b;
        colors[i].a = 255;
    }

    int indices[] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometryRaw(renderer, nullptr, xy, 2 * sizeof(float), colors, sizeof(SDL_Color), nullptr, 0, 4, indices, 6, sizeof(int));

    // Pour afficher les contours
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
    SDL_RenderDrawLine(renderer, points[1].x, points[1].y, points[2].x, points[2].y);
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[3].x, points[3].y);
    SDL_RenderDrawLine(renderer, points[3].x, points[3].y, points[0].x, points[0].y);
}

