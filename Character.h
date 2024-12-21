#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <GL/glut.h>
//#include "CollisionUtils.h"
#include <string>
#include <vector>

extern bool jumpKey;
extern bool moveLeftKey;
extern bool moveRightKey;
// Screen boundaries
const float SCREEN_LEFT = -1.0f;
const float SCREEN_RIGHT = 1.0f;
const float SCREEN_BOTTOM = -1.0f;
const float SCREEN_TOP = 1.0f;
extern float groundLevel;

// Bullet Class
class Bullet {
public:
    float x, y;
    float dx, dy;
    float speed;
    float width, height;
    bool isActive;
    float BulletWidth = 0.2f, BulletHeight = 0.2f;
    GLuint BulletTexture;

    Bullet(float x, float y, float dx, float dy, float speed)
        : x(x), y(y), dx(dx), dy(dy), speed(speed), isActive(true) {
        width = 0.05f;
        height = 0.05f;
    }

    void update();
    void draw() const;
    float getX() const{
        return x;
    }
    float getY() const {
        return y;
    }
    float getWidth() const {
        return width;
    }
    float getHeight() const {
        return height;
    }
    void deactivate() { isActive = false; }
    
};

// Character Class
class Character {
private:
    static const int MAX_TEXTURES = 10;
    GLuint textures[MAX_TEXTURES];
    int textureCount;
    int currentStep;
    float x, y;
    float width, height;
    float speedX, speedY;
    float animationSpeed;
    float lastUpdateTime;
    float Health = 100.0f;
    bool isFacingLeft = false;
    bool isOnGround = false;

    float airPauseTime = 0.0f;
    const float maxAirPause = 0.2f;

    // Floating Gun
    GLuint gunTexture;
    float gunWidth = 0.2f, gunHeight = 0.2f;
    float gunAngle = 0.0f;
    float mouseX = 0.0f, mouseY = 0.0f;

    // Bullets
    GLuint BulletTexture;
    std::vector<Bullet> bullets;
    float bulletSpeed = 0.2f;


public:
    // Constructor
    Character(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed);

    // Destructor
    ~Character();

    // Methods to manage character
    void loadTextures(const std::string texturePaths[], int count);
    void update();
    void draw();
    void moveLeft();
    void moveRight();
    void jump(float jumpSpeed);
    float getX() const { return x; }
    /*Bullet*/
    void loadBulletTexture(const std::string& BullettexturePath);

    // Gun
    void loadGunTexture(const std::string& gunTexturePath);
    void updateGunRotation(float mouseX, float mouseY);
    void drawGun() const;
    void fireBullet();
    void updateBullets();
    void drawBullets() const;

    std::vector<Bullet>& getBullets();


    
};

#endif // CHARACTER_H
