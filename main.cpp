#include <GL/glut.h>
#include "Character.h"
#include "Zombie.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include <string>
#include <iostream>
#include <sstream>
#include "stb_image.h"

int score = 0;
float timer = 90.0f; // Timer starts at 60 seconds
bool isRunning = true;

Level_1_Arena* level1;
Level_2_Arena* level2;
Level_3_Arena* level3;
Bullet* bullet;
Character* character;
Zombie2* zombie1;
Zombie2* zombie2;
Zombie2* zombie3;
Zombie2* zombie4;
Zombie2* zombie5;
Zombie2* zombie6;
Zombie2* zombie7;
Zombie2* zombie8;
Zombie2* zombie9;

bool moveLeftKey = false;
bool moveRightKey = false;
bool jumpKey = false;

void OnKeyPress(unsigned char key, int x, int y);
void OnKeyRelease(unsigned char key, int x, int y);
void handleSpecialKeyPress(int key, int x, int y);
void handleSpecialKeyRelease(int key, int x, int y);
void mouseMotionCallback(int x, int y);
void handleMouseClick(int button, int state, int x, int y);
// Cleanup resources
void cleanup() {
    delete character;
    delete zombie1;
    delete zombie2;
    delete zombie3;
    delete zombie4;
    delete zombie5;
    delete zombie6;
    delete zombie7;
    delete zombie8;
    delete zombie9;
}
void exitProgram() {
    cleanup();
    exit(0); // Exit the program
}

//------------------------------------------------Timer and Score--------------------------------------------//

void renderBitmapString(float x, float y, void *font, const std::string &string) {
    glRasterPos2f(x, y);
    for (char c : string) {
        glutBitmapCharacter(font, c);
    }
}

void Print_Score() {
    
    
    //glutSwapBuffers();
}

void update(int value) {
    if (isRunning) {
        // Update timer
        timer -= 0.1f;
        if (timer <= 0) {
            timer = 0;
            std::cout << "Time's up!" << std::endl;
            isRunning = false;
        }

        // Redraw the screen
        glutPostRedisplay();

        // Schedule the next update
        glutTimerFunc(100, update, 0);
    }
}
void addScore(int points) {
    score += points;
    std::cout << "Score: " << score << std::endl;
}

void renderHUD() {
    std::string scoreText = "Score: " + std::to_string(score);
    std::string timerText = "Time: " + std::to_string((int)timer);

    // Set text color
    glColor3f(1.0f, 1.0f, 1.0f);

    // Render score
    glRasterPos2f(-0.95f, 0.9f); // Top-left corner
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Render timer
    glRasterPos2f(0.7f, 0.9f); // Top-right corner
    for (char c : timerText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    // Set text color to white
    glColor3f(1.0, 1.0, 1.0);

    // Display timer
    std::ostringstream timerStream;
    timerStream << "Time: " << (int)timer;
    renderBitmapString(-0.9f, 0.9f, GLUT_BITMAP_HELVETICA_18, timerStream.str());

    // Display score
    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;
    renderBitmapString(-0.9f, 0.8f, GLUT_BITMAP_HELVETICA_18, scoreStream.str());
}

/*---------------------------------------Initialize OpenGL settings and load character----------------------*/
void initialize() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency

    // Create a character
    character = new Character(0.05f, -1.0f, 0.2f, 0.2f, 0.0005f, 0.0005f, 0.2f);
    const std::string texturePaths[] = { "images/Hero/Pose_1.png", "images/Hero/Pose_2.png" };
    character->loadTextures(texturePaths, 2);
    const std::string gunTexturePath = "images/Hero/Gun.png";
    character->loadGunTexture(gunTexturePath);

    character->loadBulletTexture("images/Bullets/fire.png");

    //timer and score
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);


    /*---------------------------------------------------Level1-----------------------------------------*/
    // Create Zombie
    zombie7 = new Zombie2(0.5f, -1.0f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie7Textures[] = {
        "images/Low_Zombie/Z_1/Level_1-1.png",
        "images/Low_Zombie/Z_1/Level_1-2.png",
        "images/Low_Zombie/Z_1/Level_1-3.png",
        "images/Low_Zombie/Z_1/Level_1-4.png"
    };
    zombie7->loadZombie(zombie7Textures, 4);

    // Create Zombie2
    zombie8 = new Zombie2(-1.0f, -1.0f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie8Textures[] = {
        "images/Low_Zombie/Z_2/Zombie_2_1.png",
        "images/Low_Zombie/Z_2/Zombie_2_2.png",
        "images/Low_Zombie/Z_2/Zombie_2_3.png"
    };
    zombie8->loadZombie(zombie8Textures, 3);


    // Create Zombie3
    zombie9 = new Zombie2(0.5f, -0.5f, 0.1f, 0.2f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie9Textures[] = {
        "images/Low_Zombie/Z_3/Zombie_3_1.png",
        "images/Low_Zombie/Z_3/Zombie_3_2.png",

    };
    zombie9->loadZombie(zombie9Textures, 2);

    /*---------------------------------------------------Level2-----------------------------------------*/
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


    /*---------------------------------------------------Level3-----------------------------------------*/
   // Create Zombie
    zombie4 = new Zombie2(0.5f, -1.0f, 0.3f, 0.3f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie_High_Textures[] = {
        "images/Higher_level/Z_5/z_5_1.png",
        "images/Higher_level/Z_5/z_5_2.png",
        "images/Higher_level/Z_5/z_5_3.png",
        "images/Higher_level/Z_5/z_5_4.png"
    };
    zombie4->loadZombie(zombie_High_Textures, 4);

    // Create Zombie2
    zombie5 = new Zombie2(-1.0f, -1.0f, 0.3f, 0.3f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie2_High_Textures[] = {
        "images/Higher_level/Z_4/Z_4_1.png",
        "images/Higher_level/Z_4/Z_4_2.png",
        "images/Higher_level/Z_4/Z_4_3.png"
    };
    zombie5->loadZombie(zombie2_High_Textures, 3);


    // Create Zombie3
    zombie6 = new Zombie2(0.5f, -0.5f, 0.2f, 0.3f, 0.0005f, 0.0005f, 1.0f, character);
    const std::string zombie3_High_Textures[] = {
        "images/Low_Zombie/Z_2/Zombie_2_4.png",
        "images/Low_Zombie/Z_2/Zombie_2_5.png",

    };
    zombie6->loadZombie(zombie3_High_Textures, 2);


    std::string side = "images/backGround/side.png";
    std::string mid = "images/backGround/mid.png";

    // create level1 arena
    level1 = new  Level_1_Arena();
    std::string back1 = "images/backGround/level1.jpg";
    level1->init(back1, side, side, mid); // Path to your background image

    // create level2 Arena
    level2 = new  Level_2_Arena();
    std::string back2 = "images/backGround/level2.jpg";
    level2->init(back2, side, side, mid, side);

    //create level3 arena
    level3 = new  Level_3_Arena();
    std::string back3 = "images/backGround/level3.jpg";
    level3->init(back3, side, side, mid, side);


}

/*---------------------------------------Check Zombie and Bullet Collision-------------------------------*/

void checkBulletCollision(Bullet& bullet, Zombie& zombie) {
    if (bullet.isActive && !zombie.isDead() &&
        bullet.getX() < zombie.getX() + zombie.getWidth() &&
        bullet.getX() + bullet.getWidth() > zombie.getX() &&
        bullet.getY() < zombie.getY() + zombie.getHeight() &&
        bullet.getY() + bullet.getHeight() > zombie.getY()) {
        addScore(1);
        zombie.takeHit();
        bullet.deactivate();
    }
}

/*---------------------------------------Display function-----------------------------------------------*/
enum GameState {
    INTRO_MENU,
    LEVEL_SELECTION,
    GAME_LEVEL_1,
    GAME_LEVEL_2,
    GAME_LEVEL_3
};

GameState currentState = INTRO_MENU;

// Define regions for menu options (adjust values to match your layout)
struct Region {
    float xMin, xMax, yMin, yMax;
    GLuint textureID;
};

Region playButton = { -0.5f, 0.5f, 0.2f, 0.4f, 0 };
Region aboutUsButton = { -0.5f, 0.5f, -0.2f, 0.0f, 0 };
Region exitButton = { -0.5f, 0.5f, -0.6f, -0.4f, 0 };

Region level1Button = { -0.5f, 0.5f, 0.2f, 0.4f, 0 };
Region level2Button = { -0.5f, 0.5f, -0.2f, 0.0f, 0 };
Region level3Button = { -0.5f, 0.5f, -0.6f, -0.4f, 0 };
Region menuBackground = { -1.0f, 1.0f, -1.0f, 1.0f, 0 };

GLuint loadTexture(const char* filename) {
    GLuint texture;
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }
    else {
        std::cout << "Texture loaded successfully: " << filename << std::endl;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    GLenum format = (channels == 4) ? GL_RGBA : (channels == 3) ? GL_RGB : GL_LUMINANCE;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return texture;
}

void initializeTextures() {

    
    playButton.textureID = loadTexture("images/backGround/1.png");
    aboutUsButton.textureID = loadTexture("images/backGround/2.png");
    exitButton.textureID = loadTexture("images/backGround/3.png");

    level1Button.textureID = loadTexture("images/backGround/4.png");
    level2Button.textureID = loadTexture("images/backGround/5.png");
    level3Button.textureID = loadTexture("images/backGround/6.png");

    menuBackground.textureID = loadTexture("images/backGround/level3.jpg");
}


void Character::takeHit() {

    Health -= 20.0f; // Adjust damage as needed
    if (Health <= 0.0f) {
        Health = 0.0f; // Prevent negative health
    }
    if (x == zombie4->getX()) {
        disappear();
    }
}

// Make the zombie disappear
void Character::disappear() {

    x = -100.0f;
    y = -100.0f;
    speedX = 0.0f;
    speedY = 0.0f;
}

void drawTexturedButton(const Region& button) {
    if (button.textureID == 0) return; // Skip if texture not set

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, button.textureID);


    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(button.xMin, button.yMax);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(button.xMax, button.yMax);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(button.xMax, button.yMin);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(button.xMin, button.yMin);
    glEnd();

}

void renderMenu() {
    
    if (currentState == INTRO_MENU) {
        drawTexturedButton(playButton);
        drawTexturedButton(aboutUsButton);
        drawTexturedButton(exitButton);
    }
    else if (currentState == LEVEL_SELECTION) {
        drawTexturedButton(level1Button);
        drawTexturedButton(level2Button);
        drawTexturedButton(level3Button);
    }
}


// Check if a point is inside a region
bool isInsideRegion(int mouseX, int mouseY, const Region& region) {
    float normalizedX = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2.0f - 1.0f;
    float normalizedY = -((mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2.0f - 1.0f);


    return normalizedX >= region.xMin && normalizedX <= region.xMax &&
        normalizedY >= region.yMin && normalizedY <= region.yMax;
}

void handleMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (currentState == INTRO_MENU || currentState == LEVEL_SELECTION) {
            // Handle menu interactions
            switch (currentState) {
            case INTRO_MENU:
                if (isInsideRegion(x, y, playButton)) {
                    
                    currentState = LEVEL_SELECTION;
                    glutPostRedisplay();
                }
                else if (isInsideRegion(x, y, aboutUsButton)) {
                    std::cout << "About Us: This game is created by [Your Name]." << std::endl;
                    
                    glutPostRedisplay();
                }
                else if (isInsideRegion(x, y, exitButton)) {
                    exitProgram();
                }
                break;

            case LEVEL_SELECTION:
                if (isInsideRegion(x, y, level1Button)) {
                    currentState = GAME_LEVEL_1;
                    glutPostRedisplay();
                }
                else if (isInsideRegion(x, y, level2Button)) {
                    currentState = GAME_LEVEL_2;
                    glutPostRedisplay();
                }
                else if (isInsideRegion(x, y, level3Button)) {
                    currentState = GAME_LEVEL_3;
                    glutPostRedisplay();
                }
                break;

            default:
                break;
            }
            glutPostRedisplay();
        }
        else if (currentState == GAME_LEVEL_1 || currentState == GAME_LEVEL_2 || currentState == GAME_LEVEL_3) {
            character->update();
            character->draw();
            // Update and draw bullets
            character->updateBullets();
            character->drawBullets();

            character->fireBullet();

            for (Bullet& bullet : character->getBullets()) {
                if (bullet.isActive) {
                    checkBulletCollision(bullet, *zombie1);
                    checkBulletCollision(bullet, *zombie2);
                    checkBulletCollision(bullet, *zombie3);
                }
            }
        }
    }
}




void displayMenu() {
    // Render the menu based on currentState
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    if (currentState == INTRO_MENU) {
        // Draw Intro Menu (Play, About Us, Exit)
        drawTexturedButton(menuBackground);
        renderMenu();

    }
    else if (currentState == LEVEL_SELECTION) {
        // Draw Level Selection Menu (Level 1, Level 2, Level 3)
        std::cout << "Rendering LEVEL_SELECTION menu..." << std::endl;
        drawTexturedButton(menuBackground);
        renderMenu();

    }
    else if (currentState == GAME_LEVEL_1 || currentState == GAME_LEVEL_2 || currentState == GAME_LEVEL_3) {
        switch (currentState) {
        case GAME_LEVEL_1:
            level1->draw();
            character->update();
            character->draw();

            // Update and draw bullets
            character->updateBullets();
            character->drawBullets();

            // Update and draw Zombie
            zombie7->update();
            zombie7->draw();

            zombie8->update();
            zombie8->draw();

            zombie9->update();
            zombie9->draw();

            // Collision checking
            for (Bullet& bullet : character->getBullets()) {
                if (bullet.isActive) {
                    checkBulletCollision(bullet, *zombie7);
                    checkBulletCollision(bullet, *zombie8);
                    checkBulletCollision(bullet, *zombie9);
                }
            }


            renderHUD();
            break;
        case GAME_LEVEL_2:
            level2->draw();

            character->update();
            character->draw();

            // Update and draw bullets
            character->updateBullets();
            character->drawBullets();

            // Update and draw Zombie
            zombie1->update();
            zombie1->draw();

            zombie2->update();
            zombie2->draw();

            zombie4->update();
            zombie4->draw();

            // Collision checking
            for (Bullet& bullet : character->getBullets()) {
                if (bullet.isActive) {
                    checkBulletCollision(bullet, *zombie1);
                    checkBulletCollision(bullet, *zombie2);
                    checkBulletCollision(bullet, *zombie3);
                }
            }

            renderHUD();
            break;
        case GAME_LEVEL_3:
            level3->draw();
            character->update();
            character->draw();

            // Update and draw bullets
            character->updateBullets();
            character->drawBullets();

            // Update and draw Zombie
            zombie4->update();
            zombie4->draw();

            zombie5->update();
            zombie5->draw();

            zombie6->update();
            zombie6->draw();
            // Collision checking
            for (Bullet& bullet : character->getBullets()) {
                if (bullet.isActive) {
                    checkBulletCollision(bullet, *zombie4);
                    checkBulletCollision(bullet, *zombie5);
                    checkBulletCollision(bullet, *zombie6);
                }
            }
            renderHUD();
            break;
        }
        
    }
    
    glutSwapBuffers();
}
    
    
    




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Zombie Survival");

    // Register keyboard callbacks
    glutKeyboardFunc(OnKeyPress);
    glutKeyboardUpFunc(OnKeyRelease);

    glutSpecialFunc(handleSpecialKeyPress);
    glutSpecialUpFunc(handleSpecialKeyRelease);

    glutPassiveMotionFunc(mouseMotionCallback);
    glutMouseFunc(handleMouseClick);

    initialize();
    initializeTextures();
    atexit(cleanup); // Register cleanup function

    glutDisplayFunc(displayMenu);
    glutIdleFunc(displayMenu);
    
    glutTimerFunc(100, update, 0);

    glutMainLoop();
    return 0;
}


//Menu for selct level and intro Not used as it's if to add text to opengl
void renderIntroMenu() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.3f, 0.5f);
    const char* title = "Welcome to the Game!";
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, 0.2f);
    const char* playOption = "1. Play";
    for (const char* c = playOption; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, -0.1f);
    const char* aboutOption = "2. About Us";
    for (const char* c = aboutOption; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, -0.4f);
    const char* exitOption = "3. Exit";
    for (const char* c = exitOption; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void renderLevelSelectionMenu() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.3f, 0.5f);
    const char* title = "Select Level";
    for (const char* c = title; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, 0.2f);
    const char* level1Option = "1. Level 1";
    for (const char* c = level1Option; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, -0.1f);
    const char* level2Option = "2. Level 2";
    for (const char* c = level2Option; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glRasterPos2f(-0.4f, -0.4f);
    const char* level3Option = "3. Level 3";
    for (const char* c = level3Option; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}





void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // ESC key
        exitProgram();
    }
}
/*----------------------------------------------Controls------------------------------------------*/
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

void mouseMotionCallback(int x, int y) {
    // Replace windowWidth and windowHeight with actual variables for your window dimensions
    float normalizedX = (x / (float)800) * 2.0f - 1.0f; // Normalize to [-1, 1]
    float normalizedY = -((y / (float)600) * 2.0f - 1.0f); // Normalize to [-1, 1], flip y-axis

    // Assuming `character` is a global or accessible instance of your Character class
    character->updateGunRotation(normalizedX, normalizedY);
}

