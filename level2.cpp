#include "level2.h"
#include "stb_image.h"
#include <iostream>
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F

Level_2_Arena::Level_2_Arena()
    : backgroundTextureID(0), overlayLeftTextureID(0), overlayRightTextureID(0), overlayBottomMidTextureID(0), overlayMiddleTextureID(0),
    backgroundWidth(0), backgroundHeight(0), backgroundChannels(0),
    overlayLeftWidth(0), overlayLeftHeight(0), overlayLeftChannels(0),
    overlayRightWidth(0), overlayRightHeight(0), overlayRightChannels(0),
    overlayBottomMidWidth(0), overlayBottomMidHeight(0), overlayBottomMidChannels(0),
    overlayMiddleWidth(0), overlayMiddleHeight(0), overlayMiddleChannels(0) {}

Level_2_Arena::~Level_2_Arena() {
    if (backgroundTextureID) glDeleteTextures(1, &backgroundTextureID);
    if (overlayLeftTextureID) glDeleteTextures(1, &overlayLeftTextureID);
    if (overlayRightTextureID) glDeleteTextures(1, &overlayRightTextureID);
    if (overlayBottomMidTextureID) glDeleteTextures(1, &overlayBottomMidTextureID);
    if (overlayMiddleTextureID) glDeleteTextures(1, &overlayMiddleTextureID);  // Delete the new overlay texture
}

void Level_2_Arena::loadTexture(const std::string& imagePath, GLuint& textureID, int& width, int& height, int& channels) {
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        std::cout << "Texture loaded: " << imagePath << std::endl;
    }
    else {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
    }
}

void Level_2_Arena::init(const std::string& backgroundPath, const std::string& overlayPathLeft,
    const std::string& overlayPathRight, const std::string& overlayPathBottomMid, const std::string& overlayPathMiddle) {
    loadTexture(backgroundPath, backgroundTextureID, backgroundWidth, backgroundHeight, backgroundChannels);
    loadTexture(overlayPathLeft, overlayLeftTextureID, overlayLeftWidth, overlayLeftHeight, overlayLeftChannels);
    loadTexture(overlayPathRight, overlayRightTextureID, overlayRightWidth, overlayRightHeight, overlayRightChannels);
    loadTexture(overlayPathBottomMid, overlayBottomMidTextureID, overlayBottomMidWidth, overlayBottomMidHeight, overlayBottomMidChannels);
    loadTexture(overlayPathMiddle, overlayMiddleTextureID, overlayMiddleWidth, overlayMiddleHeight, overlayMiddleChannels);  // Load new middle overlay
}

void Level_2_Arena::draw() {
    // Draw the background
    if (backgroundTextureID) {
        glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);  // Bottom-left
        glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);   // Bottom-right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);    // Top-right
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);   // Top-left
        glEnd();
    }

    // Draw the left overlay at a custom position
    if (overlayLeftTextureID) {
        glBindTexture(GL_TEXTURE_2D, overlayLeftTextureID);
        glBegin(GL_QUADS);
        float rectWidth = 0.6f;
        float rectHeight = 0.07f;
        float left = -1.0f;
        float right = left + rectWidth;
        float bottom = -0.3f;  // Position left overlay at a new Y value
        float top = bottom + rectHeight;

        glTexCoord2f(0.0f, 0.0f); glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(left, top);
        glEnd();
    }

    // Draw the right overlay at a custom position
    if (overlayRightTextureID) {
        glBindTexture(GL_TEXTURE_2D, overlayRightTextureID);
        glBegin(GL_QUADS);
        float rectWidth = 0.6f;
        float rectHeight = 0.07f;
        float right = 1.0f;
        float left = right - rectWidth;
        float bottom = -0.55f;  // Position right overlay at a new Y value
        float top = bottom + rectHeight;

        glTexCoord2f(0.0f, 0.0f); glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(left, top);
        glEnd();
    }

    // Draw the bottom middle overlay at a custom position
    if (overlayBottomMidTextureID) {
        glBindTexture(GL_TEXTURE_2D, overlayBottomMidTextureID);
        glBegin(GL_QUADS);

        float rectWidth = 0.06f;
        float rectHeight = 0.7f;
        float center = 0.0f;

        float left = center - rectWidth / 2.0f;
        float right = center + rectWidth / 2.0f;

        float top = 1.0f;
        float bottom = top - rectHeight;

        glTexCoord2f(0.0f, 0.0f); glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(left, top);

        glEnd();
    }


    // Draw the middle overlay at a custom position
    if (overlayMiddleTextureID) {
        glBindTexture(GL_TEXTURE_2D, overlayMiddleTextureID);
        glBegin(GL_QUADS);
        float rectWidth = 0.6f;
        float rectHeight = 0.07f;
        float left = -0.3f;  // New position for middle overlay
        float right = left + rectWidth;
        float bottom = 0.3f;  // Middle overlay at new Y value
        float top = bottom + rectHeight;

        glTexCoord2f(0.0f, 0.0f); glVertex2f(left, bottom);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(right, bottom);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(right, top);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(left, top);
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind textures
}

#endif
