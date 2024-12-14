#include "Character.h"
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

// Helper function to load a texture
GLuint loadTexture(const std::string& filePath) {
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
Character::Character(float x, float y, float width, float height, float speedX, float speedY, float animationSpeed)
    : x(x), y(y), width(width), height(height), speedX(speedX), speedY(speedY), animationSpeed(animationSpeed), currentStep(0), lastUpdateTime(0.0f), textureCount(0) {}

// Destructor
Character::~Character() {
    for (int i = 0; i < textureCount; ++i) {
        glDeleteTextures(1, &textures[i]);
    }
}

// Load textures from file paths
void Character::loadTextures(const std::string texturePaths[], int count) {
    if (count > MAX_TEXTURES) {
        std::cerr << "Too many textures! Only the first " << MAX_TEXTURES << " will be loaded." << std::endl;
        count = MAX_TEXTURES;
    }

    for (int i = 0; i < count; ++i) {
        GLuint textureID = loadTexture(texturePaths[i]);
        if (textureID != 0) {
            textures[textureCount++] = textureID; // Increment texture count
        }
    }
}

// Update character's position and animation
void Character::update() {
    // To stop movement, don't update x and y
    // x += speedX;
    // y += speedY;

    // Bounce off boundaries (if needed, remove these lines to prevent bouncing)
    // if (x < -1.0f || x > 1.0f - width) speedX = -speedX;
    // if (y < -1.0f || y > 1.0f - height) speedY = -speedY;

    // Update animation
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 5000.0f;
    if (currentTime - lastUpdateTime > animationSpeed && textureCount > 0) {
        currentStep = (currentStep + 1) % textureCount;
        lastUpdateTime = currentTime;
    }
}

// Draw the character
void Character::draw() const {
    if (textureCount == 0) return;

    glBindTexture(GL_TEXTURE_2D, textures[currentStep]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    glEnd();
}
