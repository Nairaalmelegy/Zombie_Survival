#ifndef LEVEL2_H
#define LEVEL2_H
#include <GL/glut.h>
#include <string>

class Level_2_Arena {
public:
    Level_2_Arena();
    ~Level_2_Arena();

    // Initialize the background and overlay textures
    void init(const std::string& backgroundPath, const std::string& overlayPathLeft, const std::string& overlayPathRight,
        const std::string& overlayPathBottomMid, const std::string& overlayPathMiddle);

    // Draw the background and overlay textures
    void draw();

private:
    GLuint backgroundTextureID;
    GLuint overlayLeftTextureID;
    GLuint overlayRightTextureID;
    GLuint overlayBottomMidTextureID;
    GLuint overlayMiddleTextureID;  // New overlay texture

    int backgroundWidth, backgroundHeight, backgroundChannels;
    int overlayLeftWidth, overlayLeftHeight, overlayLeftChannels;
    int overlayRightWidth, overlayRightHeight, overlayRightChannels;
    int overlayBottomMidWidth, overlayBottomMidHeight, overlayBottomMidChannels;
    int overlayMiddleWidth, overlayMiddleHeight, overlayMiddleChannels;  // New overlay dimensions

    // Load a texture from an image file
    void loadTexture(const std::string& imagePath, GLuint& textureID, int& width, int& height, int& channels);
};

#endif
