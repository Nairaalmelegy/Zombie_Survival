#pragma once

#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Character.h"
#include <GL/glut.h>
#include <string>
//#include "CollisionUtils.h"


// Forward declaration to avoid unnecessary coupling
class Character;

class Zombie {
protected:
    static constexpr int MAX_TEXTURES = 10;
    GLuint textures[MAX_TEXTURES];
    int textureCount;
    int currentStep;

    float x, y;
    float width, height;
    float speedX, speedY;
    float animationSpeed;
    float lastUpdateTime;

    float health;
    Character* target;

    int hitCount;
    const int maxHits = 5;
    
public:
    // Constructor and destructor
    Zombie(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target);
    ~Zombie();

    // Methods
    void loadZombie(const std::string texturePaths[], int count);
    virtual void update();
    virtual void draw() const;

    // Getters and setters
    float getX() const { return x; }
    float getY() const { return y; }
    float getHealth() const { return health; }
    void setHealth(float newHealth) { health = newHealth; }
    void takeDamage(float damage) { health -= damage; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    bool isDead() const { return health <= 0; }
    
    // Method to handle being hit
    void takeHit() {
        hitCount++;
        health -= 20.0f; // Adjust damage as needed
        if (health <= 0.0f) {
            health = 0.0f; // Prevent negative health
        }
        if (hitCount >= maxHits) {
            disappear();
        }
    }

    // Make the zombie disappear
    void disappear() {
        
        x = -100.0f;
        y = -100.0f;
        speedX = 0.0f;
        speedY = 0.0f;
    }

    

};

class Zombie2 : public Zombie {
private:
    bool isFacingRight; // Track the direction the zombie is facing
public:
    // Constructor (properly defined outside class)
    Zombie2(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target);

    void update() override;
    void draw() const override;
    //void checkCollision(const Bullet* bullet);

};

#endif // ZOMBIE_H
