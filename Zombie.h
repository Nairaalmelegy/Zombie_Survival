#pragma once

#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Character.h"
#include <GL/glut.h>
#include <string>

// Forward declaration to avoid unnecessary coupling
class Character;

class Zombie {
protected:
    static constexpr int MAX_TEXTURES = 10; // Maximum number of textures
    GLuint textures[MAX_TEXTURES];          // Texture IDs
    int textureCount;                       // Number of loaded textures
    int currentStep;                        // Current animation step

    float x, y;                             // Position
    float width, height;                    // Size
    float speedX, speedY;                   // Movement speed
    float animationSpeed;                   // Speed of animation transitions
    float lastUpdateTime;                   // Last time the animation was updated

    float health;                           // Zombie's health
    Character* target;                      // Pointer to the target character

public:
    // Constructor and destructor
    Zombie(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target);
    ~Zombie();

    // Methods
    void loadZombie(const std::string texturePaths[], int count); // Load textures
    virtual void update();                                               // Update position and animation
    virtual void draw() const;                                           // Draw the zombie on the screen

    // Getters and setters
    float getX() const { return x; }
    float getY() const { return y; }
    float getHealth() const { return health; }
    void setHealth(float newHealth) { health = newHealth; }
    void takeDamage(float damage) { health -= damage; }

    bool isDead() const { return health <= 0; }
};

class Zombie2 : public Zombie {
private:
    bool isFacingRight; // Track the direction the zombie is facing
public:
    // Constructor (properly defined outside class)
    Zombie2(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target);

    void update() override;
    void draw() const override;

};

#endif // ZOMBIE_H
