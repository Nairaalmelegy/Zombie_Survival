#include <GL/glut.h>
#include "Character.h"
#include "Zombie.h"

Character* character;
Zombie* zombie1;
Zombie2* zombie2;

// Initialize OpenGL settings and load character
void initialize() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency

    // Create a character
    character = new Character(0.05f, -1.0f, 0.2f, 0.2f, 0.0f, 0.0f, 0.2f);

    // Load textures for the character
    const std::string texturePaths[] = { "images/Hero/Pose_1.png", "images/Hero/Pose_2.png" };
    character->loadTextures(texturePaths, 2); // Provide array and count

    // Create Zombie
    zombie1 = new Zombie(0.5f, -1.0f, 0.1f, 0.2f, 0.001f, 0.005f, 1.0f, character);
    const std::string zombieTextures[] = {
        "images/Low_Zombie/Z_1/Level_1-1.png",
        "images/Low_Zombie/Z_1/Level_1-2.png",
        "images/Low_Zombie/Z_1/Level_1-3.png",
        "images/Low_Zombie/Z_1/Level_1-4.png"
    };
    zombie1->loadZombie(zombieTextures, 4);


    zombie2 = new Zombie2(-1.0f, -1.0f, 0.1f, 0.2f, 0.001f, 0.005f, 1.0f, character);
    const std::string zombie2Textures[] = {
        "images/Low_Zombie/Z_2/Zombie_2_1.png",
        "images/Low_Zombie/Z_2/Zombie_2_2.png",
        "images/Low_Zombie/Z_2/Zombie_2_3.png"
    };
    zombie2->loadZombie(zombie2Textures, 3);

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
    glutSwapBuffers();
}

// Cleanup resources
void cleanup() {
    delete character;
    delete zombie1;
    delete zombie2;
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

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Character Animation");

    initialize();
    atexit(cleanup); // Register cleanup function

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard); // Handle keyboard input

    glutMainLoop();
    return 0;
}
