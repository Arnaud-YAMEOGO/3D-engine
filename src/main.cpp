#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Sdl.h"
#include "Scene3D.h"

// Dimensions de la fenêtre
const int WIDTH = 800;
const int HEIGHT = 600;

extern float rotationX;
extern float rotationY;
extern float translationX;
extern float translationY;
extern float translationZ;

/**
 * @brief Main function.
 * @return 0 if successful
 */
int main() {
    Sdl sdl("3D Cube and Sphere", WIDTH, HEIGHT);
    Scene3D scene;

    auto cube = scene.generateCube();
    auto sphere = scene.generateSphere(20, 20);

    bool running = true;
    SDL_Event event;

    bool keys[SDL_NUM_SCANCODES] = {false}; // Tableau pour stocker l'état des touches
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
               keys[event.key.keysym.scancode] = true;
             }else if (event.type == SDL_KEYUP) {
                 keys[event.key.keysym.scancode] = false;
            }
        }

    // Gestion des transformations basées sur l'état des touches
        if (keys[SDL_SCANCODE_UP]) rotationX -= 0.1f;
        if (keys[SDL_SCANCODE_DOWN]) rotationX += 0.1f;
        if (keys[SDL_SCANCODE_LEFT]) rotationY -= 0.1f;
        if (keys[SDL_SCANCODE_RIGHT]) rotationY += 0.1f;
        if (keys[SDL_SCANCODE_W]) translationZ += 0.5f;
        if (keys[SDL_SCANCODE_S]) translationZ -= 0.5f;
        if (keys[SDL_SCANCODE_A]) translationX -= 0.5f;
        if (keys[SDL_SCANCODE_D]) translationX += 0.5f;
        if (keys[SDL_SCANCODE_Q]) translationY += 0.5f;
        if (keys[SDL_SCANCODE_E]) translationY -= 0.5f;

        SDL_SetRenderDrawColor(sdl.renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdl.renderer);

        // Rotation et décalage du cube
        std::vector<Quad3D> transformedCube;
        for (const auto& quad : cube.quads) {
            Quad3D transformed = quad;
            transformed.v1 = scene.rotatePoint(quad.v1, rotationX, rotationY);
            transformed.v2 = scene.rotatePoint(quad.v2, rotationX, rotationY);
            transformed.v3 = scene.rotatePoint(quad.v3, rotationX, rotationY);
            transformed.v4 = scene.rotatePoint(quad.v4, rotationX, rotationY);

            transformed.v1.x -= 2.5;
            transformed.v1.z += 2;
            transformed.v2.x -= 2.5;
            transformed.v2.z += 2;
            transformed.v3.x -= 2.5;
            transformed.v3.z += 2;
            transformed.v4.x -= 2.5;
            transformed.v4.z += 2;
            transformedCube.push_back(transformed);
        }

        // Tri des faces du cube
        std::sort(transformedCube.begin(), transformedCube.end(), [&scene](const Quad3D& a, const Quad3D& b) {
            return scene.averageDepth(a) > scene.averageDepth(b);
        });

        for (const auto& quad : transformedCube) {
            scene.drawQuad(sdl.renderer, quad);
        }

       // Rotation et décalage de la sphère
       std::vector<Quad3D> transformedSphere;
       for (const auto& quad : sphere.quads) {
           Quad3D transformed = quad;
           transformed.v1 = scene.rotatePoint(quad.v1, rotationX, rotationY);
           transformed.v2 = scene.rotatePoint(quad.v2, rotationX, rotationY);
           transformed.v3 = scene.rotatePoint(quad.v3, rotationX, rotationY);
           transformed.v4 = scene.rotatePoint(quad.v4, rotationX, rotationY);

           transformed.v1.x += 1;
           transformed.v1.z -= 2;
           transformed.v2.x += 1;
           transformed.v2.z -= 2;
           transformed.v3.x += 1;
           transformed.v3.z -= 2;
           transformed.v4.x += 1;
           transformed.v4.z -= 2;

          transformedSphere.push_back(transformed);
        }

    // Tri des faces de la sphère
       std::sort(transformedSphere.begin(), transformedSphere.end(), [&scene](const Quad3D& a, const Quad3D& b) {
           return scene.averageDepth(a) > scene.averageDepth(b);
        });

        for (const auto& quad : transformedSphere) {
            scene.drawQuad(sdl.renderer, quad);
        }

        SDL_RenderPresent(sdl.renderer);
    }

    return 0;
}
