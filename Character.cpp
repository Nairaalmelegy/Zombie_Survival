#include "Character.h"
#include <GL/glu.h>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC(size) malloc(size)
#define STBI_FREE(ptr) free(ptr)
#define STBI_REALLOC(ptr, newsize) realloc(ptr, newsize)
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRINGS
#include "stb_image.h"

#include <iostream>
float groundLevel = -1.0f;


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
    : x(x), y(y), width(width), height(height), speedX(speedX), speedY(speedY), animationSpeed(animationSpeed), currentStep(0), lastUpdateTime(0.0f), textureCount(0), airPauseTime(0.0f) {}

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

/*.......................................Gun.....................................................*/
/*Load the gun texture*/
void Character::loadGunTexture(const std::string& gunTexturePath) {
    gunTexture = loadTexture(gunTexturePath); // Use the existing helper function
    gunWidth = width / 1.0f;  // Example dimensions
    gunHeight = height / 2.0f;
    gunAngle = 0.0f;          // Initialize the gun angle
}

void Character::updateGunRotation(float mx, float my) {
    mouseX = mx;
    mouseY = my;

    // Calculate angle between character and mouse
    float dx = mouseX - (x + width / 1.8f);
    float dy = mouseY - (y + height / 2.0f);
    float angle = atan2(dy, dx) * 180.0f / 3.14159f;

    
    // Adjust angle for left-facing character
    if (isFacingLeft) {
        if (angle > 180.0f) {
            angle = 180.0f;
        }
        else if (angle < 90.0f) {
            angle = 90.0f;
        }

        gunAngle = angle + 180.0f; // Adjust for left-facing
    }
    else {
        if (angle > 90.0f) {
            angle = 90.0f;
        }
        else if (angle < -90.0f) {
            angle = -90.0f;
        }

        gunAngle = angle; // Use the calculated angle as-is
    }
}

void Character::drawGun() const {
    if (gunTexture == 0) return;

    glPushMatrix();

    // Translate to character's position
    glTranslatef(x + width / 1.5f, y + height / 1.5f, 0.0f);

    if (isFacingLeft) {
        glScalef(-1.0f, 1.0f, 1.0f);
        glRotatef(-gunAngle, 0.0f, 0.0f, 1.0f);
    }
    else {
        glRotatef(gunAngle, 0.0f, 0.0f, 1.0f);
    }

    // Bind the gun texture
    glBindTexture(GL_TEXTURE_2D, gunTexture);

    // Draw the gun as a rectangle
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-gunWidth / 2.0f, -gunHeight / 2.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(gunWidth / 2.0f, -gunHeight / 2.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(gunWidth / 2.0f, gunHeight / 2.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-gunWidth / 2.0f, gunHeight / 2.0f);
    glEnd();

    glPopMatrix();
}


/*.......................................Character move.....................................................*/
void Character::moveLeft() {
    if (x - speedX >= SCREEN_LEFT) {
        x -= speedX;
        isFacingLeft = true;
    }
}

void Character::moveRight() {
    if (x + width + speedX <= SCREEN_RIGHT) {
        x += speedX;
        isFacingLeft = false;
    }
}
void Character::jump(float jumpSpeed) {
    if (isOnGround) {
        speedY = jumpSpeed;
        isOnGround = false; // Prevent jumping mid-air
    }
}

void Character::update() {
    // Apply movement if keys are pressed
    if (moveLeftKey) moveLeft();
    if (moveRightKey) moveRight();

    // Jump logic
    if (jumpKey && isOnGround) {
        jump(0.08f);
    }

    // Gravity
    const float gravity = -0.003f; // Adjust gravity magnitude
    speedY += gravity;
    y += speedY;

    // Ground collision
    if (y <= groundLevel) {
        y = groundLevel;
        speedY = 0.0f;
        isOnGround = true;
    }
    else {
        isOnGround = false;
    }

    // Animation update
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 5000.0f;
    if (currentTime - lastUpdateTime > animationSpeed && textureCount > 0) {
        currentStep = (currentStep + 1) % textureCount;
        lastUpdateTime = currentTime;
    }

    // Update bullets and remove out-of-bounds bullets
    auto it = bullets.begin();
    while (it != bullets.end()) {
        it->update();
        if (it->x < SCREEN_LEFT || it->x > SCREEN_RIGHT || it->y < SCREEN_BOTTOM || it->y > SCREEN_TOP) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

// Draw the character
void Character::draw() {
    if (textureCount == 0) return;

    // Draw character
    glBindTexture(GL_TEXTURE_2D, textures[currentStep]);
    glBegin(GL_QUADS);
    if (isFacingLeft) {
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x, y + height);
    }
    else {
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);
    }
    glEnd();

    // Draw gun
    drawGun();

    // Remove inactive bullets
    auto new_end = std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet) { return !bullet.isActive; });
    bullets.erase(new_end, bullets.end());

    // Draw bullets
    for (const auto& bullet : bullets) {
        bullet.draw();
    }
}



/*........................................................Bullets........................................*/

void Character::loadBulletTexture(const std::string& BullettexturePath) {
    BulletTexture = loadTexture(BullettexturePath);
    if (BulletTexture == 0) {
        std::cerr << "Error loading bullet texture from: " << BullettexturePath << std::endl;
    }
}


void Character::fireBullet() {
    // Ensure BulletTexture is valid
    if (BulletTexture == 0) {
        std::cerr << "Error: BulletTexture is not loaded!" << std::endl;
        return;
    }

    float bulletX = x + (isFacingLeft ? -width / 2.0f : width / 2.0f);  // Adjust the offset
    float bulletY = y + height / 1.5f;  // Adjust Y to be closer to the gun
    ////////////////////////////////////Here
    float actualGunAngle = gunAngle;
    if (isFacingLeft) {
        actualGunAngle += 180.0f; // Adjust angle for flipped direction
    }

    // Convert gunAngle from degrees to radians
    float angleRadians = actualGunAngle * 3.14159f / 180.0f;

    // Calculate bullet direction
    float bulletDx = cos(angleRadians);
    float bulletDy = sin(angleRadians);

    // Normalize direction vector
    float magnitude = sqrt(bulletDx * bulletDx + bulletDy * bulletDy);
    bulletDx /= magnitude;
    bulletDy /= magnitude;

    // Set bullet speed and direction
    float bulletSpeed = 0.02f; // Adjust this value as needed
    Bullet newBullet(bulletX, bulletY, bulletDx * bulletSpeed, bulletDy * bulletSpeed, bulletSpeed);
    newBullet.width = 0.05f;
    newBullet.height = 0.05f;

    // Assign the BulletTexture to the new bullet
    newBullet.BulletTexture = this->BulletTexture;

    // Add the bullet to the vector
    bullets.push_back(newBullet);
}



void Character::updateBullets() {
    for (auto& bullet : bullets) {
        if (bullet.isActive) {
            bullet.update();
            // Deactivate the bullet if it moves off-screen
            if (bullet.x < SCREEN_LEFT || bullet.x > SCREEN_RIGHT ||
                bullet.y < SCREEN_BOTTOM || bullet.y > SCREEN_TOP) {
                bullet.isActive = false;
            }
        }
    }

    // Remove inactive bullets from the list
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet) { return !bullet.isActive; }),
        bullets.end());
}

void Character::drawBullets() const {
    for (const auto& bullet : bullets) {
        if (bullet.isActive) {
            bullet.draw();
        }
    }
}

void Bullet::update() {
    // Move the bullet based on its direction and speed
    x += dx;
    y += dy;
}

void Bullet::draw() const {
    glBindTexture(GL_TEXTURE_2D, BulletTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x - width / 2, y - height / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width / 2, y - height / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width / 2, y + height / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x - width / 2, y + height / 2);
    glEnd();
}




