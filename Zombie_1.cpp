#include "Zombie.h"
#include "Character.h" 
#include "stb_image.h"
#include <GL/glu.h>
#include <iostream>

// Helper function to load a texture
GLuint loadZombieHelper(const std::string& filePath) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

    if (!data) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return textureID;
}

// Constructor
Zombie::Zombie(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target)
    : x(x), y(y), width(width), height(height), speedX(speedX), speedY(speedY),
    animationSpeed(animationSpeed), currentStep(0), lastUpdateTime(0.0f), textureCount(0), health(100.0f), target(target) {  // Initialize health here
    float targetx = (target ? target->getX() : 0.0f);
}

// Destructor
Zombie::~Zombie() {
    for (int i = 0; i < textureCount; ++i) {
        glDeleteTextures(1, &textures[i]);
    }
}

// Load textures from file paths
void Zombie::loadZombie(const std::string texturePaths[], int count) {
    if (count > MAX_TEXTURES) {
        std::cerr << "Too many textures! Only the first " << MAX_TEXTURES << " will be loaded." << std::endl;
        count = MAX_TEXTURES;
    }

    for (int i = 0; i < count; ++i) {
        GLuint textureID = loadZombieHelper(texturePaths[i]);
        if (textureID != 0) {
            textures[textureCount++] = textureID; // Increment texture count
        }
    }
}

// Update the zombie's position and animation
void Zombie::update() {
    if (!target) return; // No target to track

    float targetX = target->getX();

    // Move towards the target's x-coordinate
    if (x < targetX - width) {
        x += (speedX/10);
    }
    else if (x > targetX - width) {
        x -= (speedX / 10);
    }

    // Stop if at the target's position minus width
    if (fabs(x - (targetX + width)) < 0.05f) { // Close enough to stop
        speedX = 0.0f; // Stop moving
        x = targetX + width; // Ensure alignment with target
    }


    // Optional: Bounce off boundaries
     if (x < -1.0f + width || x > 1.0f - width) {
        speedX = 0;
    } 

    // Update animation
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 2000.0f;
    if (currentTime - lastUpdateTime > animationSpeed && textureCount > 0) {
        currentStep = (currentStep + 1) % textureCount;
        lastUpdateTime = currentTime;
    }
}

// Draw the zombie
void Zombie::draw() const {
    if (textureCount == 0) return; // No textures loaded

    glBindTexture(GL_TEXTURE_2D, textures[currentStep]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    glEnd();
}
/*
// Additional methods for health management
void Zombie::takeDamage(float damage) {
    Health -= damage;
    if (Health < 0.0f) {
        Health = 0.0f; // Prevent negative health
    }
}

bool Zombie::isDead() const {
    return Health <= 0;
}
*/


// Zombie 2

// Constructor for Zombie2
Zombie2::Zombie2(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed, Character* target)
    : Zombie(x, y, width, height, speedX, speedY, animationSpeed, target) {
    
}

// update the zombie's state (this is overridden from the Zombie class)

void Zombie2::update() {
    if (!target) return;

    float targetX = target->getX();

    float distance = targetX - x;

    // Always try to move towards the target (even if close)
    if (distance > 0.1) {
        x += (speedX / 8);
        isFacingRight = true;
    }
    else if (distance < -0.1) {
        x -= (speedX / 8);
        isFacingRight = false;
    }

    // screen boundaries
    if (x < -1.0f + width) x = -1.0f + width;
    if (x > 1.0f - width) x = 1.0f - width;

    // Update animation
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    if (currentTime - lastUpdateTime > animationSpeed && textureCount > 0) {
        currentStep = (currentStep + 1) % textureCount;
        lastUpdateTime = currentTime;
    }
}





void Zombie2::draw() const {
    if (textureCount == 0) return;
    glBindTexture(GL_TEXTURE_2D, textures[currentStep]);

    glBegin(GL_QUADS);

    

    if (isFacingRight) {
        // Facing left: flipped texture coordinates
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x, y + height);
        
    }
    else {
        // Facing right: normal texture coordinates
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    }

    glEnd();
}








