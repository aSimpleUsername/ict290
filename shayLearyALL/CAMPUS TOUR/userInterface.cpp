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
    std::string string = "Ammo: " + std::to_string(playerHealth);        // I think 100 health looks better than 10 health but up to you guys 
    renderText(10, 20, GLUT_BITMAP_TIMES_ROMAN_24, string);
}

void UserInterface::playerShield(int playerShield)
{
    if (playerShield < 0)       //prevents health going into negatives after death
        playerShield = 0;

    glColor3d(0.0, 0.0, 0.0);
    std::string string = "Reserve: " + std::to_string(playerShield);        // I think 100 health looks better than 10 health but up to you guys 
    renderText(10, 60, GLUT_BITMAP_TIMES_ROMAN_24, string);
}

void UserInterface::info(double x, double y, double z)
{
    std::string string = "Current location:   X = " + std::to_string(x) + ", Y = " + std::to_string(y) + ", Z = " + std::to_string(z);    
    renderText(10, 1060, GLUT_BITMAP_HELVETICA_18, string);
}

void UserInterface::hitmarker(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    if (m_hit)
    {
        m_hitTimer = glutGet(GLUT_ELAPSED_TIME) + 100;
        m_hit = false;
    }

    if (glutGet(GLUT_ELAPSED_TIME) < m_hitTimer)
    {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, screenWidth, 0, screenHeight);
        glScalef(1, -1, 1);

        // move to centre of screen
        glTranslatef(screenWidth / 2 - 25, -screenHeight / 2 - 25, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // display sign
        glBindTexture(GL_TEXTURE_2D, tempImage);
        // display image
        glCallList(358);
        // Reset Perspective Projection
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
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
    glTranslatef(0, -150, 0);
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
    glTranslatef(0, -250, 0);
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

void UserInterface::bossHealthBar(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(460, -screenHeight + 50, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(353);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::bossName(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(850, -screenHeight, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(354);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::weapon(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslated(450, -386 * 2.25, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(355);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::playerHit(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    if (m_playerHit)
    {
        m_playerHitTimer = glutGet(GLUT_ELAPSED_TIME) + 300;
        m_playerHit = false;
    }

    if (glutGet(GLUT_ELAPSED_TIME) < m_playerHitTimer)
    {
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, screenWidth, 0, screenHeight);
        glScalef(1, -1, 1);

        // move to centre of screen
        glTranslatef(0, -screenHeight, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // display sign
        glBindTexture(GL_TEXTURE_2D, tempImage);
        // display image
        glCallList(356);
        // Reset Perspective Projection
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}

void UserInterface::transparent(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(600, -screenHeight + 100, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(357);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::ammoCount1(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(1520, -250, 0);
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

void UserInterface::ammoCount2(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(1620, -250, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(359);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::rAmmoCount1(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(1670, -150, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(360);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void UserInterface::rAmmoCount2(const int& screenWidth, const int& screenHeight,
    const GLuint& tempImage)
{
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glScalef(1, -1, 1);

    // move to centre of screen
    glTranslatef(1720, -150, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // display sign
    glBindTexture(GL_TEXTURE_2D, tempImage);
    // display image
    glCallList(361);
    // Reset Perspective Projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}