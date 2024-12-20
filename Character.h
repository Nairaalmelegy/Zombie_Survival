#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <GL/glut.h>
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
    
};

// Character Class
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
    float Health = 100.0f;
    bool isFacingLeft = false;
    bool isOnGround = false;

    float airPauseTime = 0.0f;        // Time to pause in the air
    const float maxAirPause = 0.2f;

    // Floating Gun
    GLuint gunTexture;        // Gun texture
    float gunWidth = 0.2f, gunHeight = 0.2f; // Gun dimensions
    float gunAngle = 0.0f;           // Angle for gun rotation
    float mouseX = 0.0f, mouseY = 0.0f;     // Mouse coordinates for rotation calculation

    // Bullets
    GLuint BulletTexture;
    std::vector<Bullet> bullets;
    float bulletSpeed = 0.2f; // Adjust bullet speed

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
    void loadBulletTexture(const std::string& BullettexturePath); // Load bullet texture

    // Gun
    void loadGunTexture(const std::string& gunTexturePath);
    void updateGunRotation(float mouseX, float mouseY); // Update gun's rotation
    void drawGun() const;
    void fireBullet();
    void updateBullets(); // Update all active bullets
    void drawBullets() const; // Draw all active bullets
};

#endif // CHARACTER_H
