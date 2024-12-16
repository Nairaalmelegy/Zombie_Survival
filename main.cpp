#include <GL/glut.h>
#include "Character.h"
#include "Zombie.h"
#include <iostream>

Bullet* bullet;
Character* character;
Zombie2* zombie1;
Zombie2* zombie2;
Zombie2* zombie3;
bool moveLeftKey = false;
bool moveRightKey = false;
bool jumpKey = false;

void OnKeyPress(unsigned char key, int x, int y);
void OnKeyRelease(unsigned char key, int x, int y);
void handleSpecialKeyPress(int key, int x, int y);
void handleSpecialKeyRelease(int key, int x, int y);

// Initialize OpenGL settings and load character
void initialize() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency

    // Create a character
    character = new Character(0.05f, -1.0f, 0.2f, 0.2f, 0.0005f, 0.0005f, 0.2f);
    const std::string texturePaths[] = { "images/Hero/Pose_1.png", "images/Hero/Pose_2.png" };
    character->loadTextures(texturePaths, 2); 

    // Create Zombie
    zombie1 = new Zombie2(0.5f, -1.0f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombieTextures[] = {
        "images/Low_Zombie/Z_1/Level_1-1.png",
        "images/Low_Zombie/Z_1/Level_1-2.png",
        "images/Low_Zombie/Z_1/Level_1-3.png",
        "images/Low_Zombie/Z_1/Level_1-4.png"
    };
    zombie1->loadZombie(zombieTextures, 4);

    // Create Zombie2
    zombie2 = new Zombie2(-1.0f, -1.0f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie2Textures[] = {
        "images/Low_Zombie/Z_2/Zombie_2_1.png",
        "images/Low_Zombie/Z_2/Zombie_2_2.png",
        "images/Low_Zombie/Z_2/Zombie_2_3.png"
    };
    zombie2->loadZombie(zombie2Textures, 3);


    // Create Zombie3
    zombie3 = new Zombie2(0.5f, -0.5f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie3Textures[] = {
        "images/Low_Zombie/Z_3/Zombie_3_1.png",
        "images/Low_Zombie/Z_3/Zombie_3_2.png",
        
    };
    zombie3->loadZombie(zombie3Textures, 2);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    character->update();
    character->draw();

    // Update and draw Zombie
    zombie1->update();
    zombie1->draw();

    zombie2->update();
    zombie2->draw(); // Draw the second zombie

    zombie3->update();
    zombie3->draw();
    glutSwapBuffers();
}

// Cleanup resources
void cleanup() {
    delete character;
    delete zombie1;
    delete zombie2;
    delete zombie3;
}

void exitProgram() {
    cleanup();
    exit(0); // Exit the program
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exitProgram();
    }
}
/*--------------------------------------------------Control movement by keyboard--------------------------------*/



// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Character Animation");

    // Register display and update callbacks
    glutDisplayFunc(display);
    glutIdleFunc(display);

    // Register keyboard callbacks
    glutKeyboardFunc(OnKeyPress);
    glutKeyboardUpFunc(OnKeyRelease);

    glutSpecialFunc(handleSpecialKeyPress);
    glutSpecialUpFunc(handleSpecialKeyRelease);

    initialize();
    atexit(cleanup); // Register cleanup function

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard); // Handle keyboard input

    glutMainLoop();
    return 0;
}
// control with w, a, d
void OnKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': case 'W':
        jumpKey = true; // Jump
        break;
    case 'a': case 'A':
        moveLeftKey = true; // Move Left
        break;
    case 'd': case 'D':
        moveRightKey = true; // Move Right
        break;
    case 27: // ESC key
        exitProgram();
        break;
    default:
        std::cout << "Unhandled key: " << key << std::endl;
    }
}

void OnKeyRelease(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': case 'W':
        jumpKey = false; // Stop jumping
        break;
    case 'a': case 'A':
        moveLeftKey = false; // Stop moving left
        break;
    case 'd': case 'D':
        moveRightKey = false; // Stop moving right
        break;
    }
}



// control with special keys
void handleSpecialKeyPress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: // Move left
        moveLeftKey = true;
        break;
    case GLUT_KEY_RIGHT: // Move right
        moveRightKey = true;
        break;
    case GLUT_KEY_UP: // Jump
        jumpKey = true;
        break;
    }
}

void handleSpecialKeyRelease(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: // Stop moving left
        moveLeftKey = false;
        break;
    case GLUT_KEY_RIGHT: // Stop moving right
        moveRightKey = false;
        break;
    case GLUT_KEY_UP: // Jump stop
        jumpKey = false;
        break;
    }
}
