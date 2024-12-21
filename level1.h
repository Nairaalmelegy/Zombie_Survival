#ifndef LEVEL1_H
#define LEVEL1_H
#include <GL/glut.h>
#include <string>




class Level_1_Arena {
public:
    Level_1_Arena();
    ~Level_1_Arena();

    // Initialize the background and overlay textures
    void init(const std::string& backgroundPath, const std::string& overlayPathLeft, const std::string& overlayPathRight, const std::string& overlayPathBottomMid);
    // Draw the background and overlay textures
    void draw();

private:
    GLuint backgroundTextureID;
    GLuint overlayLeftTextureID;
    GLuint overlayRightTextureID;
    GLuint overlayBottomMidTextureID;

    int backgroundWidth, backgroundHeight, backgroundChannels;
    int overlayLeftWidth, overlayLeftHeight, overlayLeftChannels;
    int overlayRightWidth, overlayRightHeight, overlayRightChannels;
    int overlayBottomMidWidth, overlayBottomMidHeight, overlayBottomMidChannels;

    void loadTexture(const std::string& imagePath, GLuint& textureID, int& width, int& height, int& channels);

};

#endif

