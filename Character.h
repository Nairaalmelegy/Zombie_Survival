#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <GL/glut.h>
#include <string>

class Character {
private:
    static const int MAX_TEXTURES = 10; // Maximum number of textures
    GLuint textures[MAX_TEXTURES];
    int textureCount;       // Number of loaded textures
    int currentStep;
    float x, y;             // Position
    float width, height;    // Size
    float speedX, speedY;   // Speed for movement
    float animationSpeed;
    float lastUpdateTime;
    float Health;

public:
    // Constructor
    Character(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed);

    // Destructor
    ~Character();

    // Methods to manage character
    void loadTextures(const std::string texturePaths[], int count);
    void update();
    void draw() const;

    float getX() const { return x; }

};

#endif // CHARACTER_H
