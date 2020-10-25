#include "userInterface.h"

void UserInterface::renderText(float x, float y, void* font, std::string string)
{
    // Switch to window coordinates to render
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1920, 0, 1080);

    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2i(x, y);  // or wherever in window coordinates
    for (int i = 0; i < string.size(); ++i) {
        glutBitmapCharacter(font, string[i]);
    }

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::playerHealth(int playerHealth)
{
    if (playerHealth < 0)       //prevents health going into negatives after death
        playerHealth = 0;

    glColor3d(0.0, 0.0, 0.0);
    std::string string = "Health: " + std::to_string(playerHealth * 10);        // I think 100 health looks better than 10 health but up to you guys 
    renderText(10, 20, GLUT_BITMAP_TIMES_ROMAN_24, string);
}

void UserInterface::playerShield(int playerShield)
{
    if (playerShield < 0)       //prevents health going into negatives after death
        playerShield = 0;

    glColor3d(0.0, 0.0, 0.0);
    std::string string = "Shield: " + std::to_string(playerShield * 10);        // I think 100 health looks better than 10 health but up to you guys 
    renderText(10, 60, GLUT_BITMAP_TIMES_ROMAN_24, string);
}

void UserInterface::info(double x, double y, double z)
{
    std::string string = "Current location:   X = " + std::to_string(x) + ", Y = " + std::to_string(y) + ", Z = " + std::to_string(z);    
    renderText(10, 1060, GLUT_BITMAP_HELVETICA_18, string);
}

void UserInterface::hitmarker()
{
    if (hit)
    {
        m_timer = glutGet(GLUT_ELAPSED_TIME) + 100;
        hit = false;
    }

    if (glutGet(GLUT_ELAPSED_TIME) < m_timer)
    {
        std::string string = "HIT!";
        renderText(1920 / 2 - 20, 1080 / 2 + 50, GLUT_BITMAP_HELVETICA_18, string);
    }
}

void UserInterface::healthBar(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(0, -250, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(350);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::shieldBar(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(0, -150, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(351);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::ammoCount(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(850, -520, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(352);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}