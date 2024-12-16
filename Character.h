#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <GL/glut.h>
#include <string>

extern bool jumpKey;
extern bool moveLeftKey;
extern bool moveRightKey;

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
    bool isFacingLeft = false;
    float groundLevel = -1.0;
    float isOnGround = false;
    //Screen boundaries
    const float SCREEN_LEFT = -1.0f;
    const float SCREEN_RIGHT = 1.0f;
    const float SCREEN_BOTTOM = -1.0f;
    const float SCREEN_TOP = 1.0f;
public:
    // Constructor
    Character(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed);

    // Destructor
    ~Character();

    // Methods to manage character
    void loadTextures(const std::string texturePaths[], int count);
    void update();
    void draw() const;
    void moveLeft();
    void moveRight();
    void jump(float jumpSpeed);
    float getX() const { return x; }

};

#endif // CHARACTER_H
