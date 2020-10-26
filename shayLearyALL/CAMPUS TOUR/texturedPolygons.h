//  texturedPolygon.h
//  Header file for the texturedPolygon class
//
//
//  Shay Leary, March 2005
//--------------------------------------------------------------------------------------

#ifndef TEXTURE_POLYGON_H
#define TEXTURE_POLYGON_H

//--------------------------------------------------------------------------------------

#include <gl/glut.h>
#include <stdio.h>	// should really be using c++, but didn't get time to change
#include <stdlib.h>
#include "lodepng.h"
#include "stb_image.h"

//--------------------------------------------------------------------------------------
/**
    * @class TexturedPolygons
    * @brief Class that provides functions to texture surfaces
    * @author Group Team No Name 2
    * @version
    * @date 14 Sep 20
 */
class TexturedPolygons
{
public:

	TexturedPolygons () {}
    virtual ~TexturedPolygons () {Clear();}
    
	//----------------------------------------------------------------------------------

	/**
        * @brief Returns the texture
        * @param tempIndex - Index of texture
        * @return Gluint
    */
	GLuint GetTexture (const int & tempIndex) {return m_texture[tempIndex];}
	/**
        * @brief Loads the texture
        * @param filename - name of the file
        * @param imgWidth - width of the image
        * @param imgHeight - height of the image
        * @return GLubyte*
    */
	GLubyte* LoadTexture(char *filename, int imgWidth, int imgHeight);
    /**
        * @brief Loads the texture
        * @param textureNo - texture number
        * @param filename - name of the file
        * @return void
    */
	void LoadPNGTexture(int textureNo, const char* filename);
    /**
        * @brief Set the number of textures to be used
        * @param textureNo - number of the texture
        * @return void
    */
	void SetTextureCount(const int &textureNo);
    /**
        * @brief Creates RAW texture and set required values for texture mapping
        * @param textureNo - number of the texture
        * @param image - character array of the image
        * @param imgWidth - width of the image
        * @param imgHeight - height of the image
        * @return void
    */
	void CreateTexture(int textureNo, unsigned char* image, int imgWidth, int imgHeight);

    /**
        * @brief Calls function to creates display list to contain image
        * @param XYZ 
        * @param listNo - number the item is in the list
        * @param xImgSize - x size of image
        * @param zImgSize - z size of image
        * @param xStart - starting x
        * @param yStart - starting y
        * @param zStart - starting z
        * @param xTimes
        * @param zTimes
        * @return void
    */
	void CreateDisplayList(const int &XYZ, const int &listNo,
		                   const GLdouble &xImgSize, const GLdouble &zImgSize,
					       const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
					       const GLdouble &xTimes, const GLdouble &zTimes);

    /**
        * @brief used to create display lists where image is larger than world scale on YZ axis
        * @param listNo - number the item is in the list
        * @param xStart - starting x
        * @param yStart - starting y
        * @param ySize - size of y
        * @param zStart - starting z
        * @param zSize - size of z
        * @param yImgSize - y size of image
        * @param zImgSize - z size of image
        * @return void
    */
	void CreateYtoZWindowList(const int &listNo, const GLdouble &xStart,
							  const GLdouble &yStart, const GLdouble &ySize,
							  const GLdouble &zStart, const GLdouble &zSize,
							  const GLdouble &yImgSize, const GLdouble &zImgSize);
    /**
        * @brief Used to create display lists where image is larger than world scale on XY axis
        * @param listNo - number the item is in the list
        * @param zStart - starting z
        * @param xStart - starting x
        * @param xSize - size of x
        * @param yStart - starting y
        * @param ySize - size of y
        * @param xImgSize - y size of image
        * @param yImgSize - z size of image
        * @return void
    */

    void Clear(int size);
    void Clear();
	void CreateXtoYWindowList(const int &listNo, const GLdouble &zStart,
							  const GLdouble &xStart, const GLdouble &xSize,
							  const GLdouble &yStart, const GLdouble &ySize,
							  const GLdouble &xImgSize, const GLdouble &yImgSize);
    /**
        * @brief used to create display lists where image is on an angle
        * @param listNo - number the item is in the list
        * @param imageWidth - width of image
        * @param imageHeight - height of image
        * @param x1 - first corner x
        * @param x2 - second corner x
        * @param x3 - third corner x
        * @param x4 - fourth corner x
        * @param y1 - first corner y
        * @param y2 - second corner y
        * @param y3 - third corner y
        * @param y4 - fourth corner y
        * @param z1 - first corner z
        * @param z2 - second corner z
        * @param z3 - third corner z
        * @param z4 - fourth corner z
        * @param smallestX - the smallest x
        * @param smallestZ - the smallest z
        * @return void
    */
	void CreateAngledPolygon(const int &listNo,
							 const GLdouble &imageWidth, const GLdouble &imageHeight,
							 const GLdouble &x1, const GLdouble &x2,
							 const GLdouble &x3, const GLdouble &x4,
						     const GLdouble &y1, const GLdouble &y2,
							 const GLdouble &y3, const GLdouble &y4,
							 const GLdouble &z1, const GLdouble &z2,
							 const GLdouble &z3, const GLdouble &z4,
							 const int &smallestX, const int &smallestZ);

private:
    
	/// pointer to display list
	GLuint *m_texture;
	/**
        * @brief Loads RAW image file
        * @param filename - name of the file
        * @param width - width of the image
        * @param height - height of the image
        * @return GLubyte*
    */
	GLubyte* LoadRawImageFile(char* filename, int width, int height);

	

	// creates display list to contain image on X Z axis
	void CreateXtoZTextureList(const GLdouble &xImgSize, const GLdouble &zImgSize,
					           const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
					           const GLdouble &xTimes, const GLdouble &zTimes);

	// creates display list to contain image on X Y axis
	void CreateXtoYTextureList(const GLdouble &xImgSize, const GLdouble &yImgSize,
							   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
							   const GLdouble &xTimes, const GLdouble &yTimes, const bool &flip);

	// creates display list to contain image on Y Z axis
	void CreateYtoZTextureList(const GLdouble &yImgSize, const GLdouble &zImgSize,
							   const GLdouble &xStart, const GLdouble &yStart, const GLdouble &zStart,
							   const GLdouble &yTimes, const GLdouble &zTimes, const bool &flip);

	// called from	CreateAngledPolygon determine how images are displayed
	void CreateTextureScale(GLdouble & xzImage1, GLdouble & xzImage2,
							GLdouble & xzImage3, GLdouble & xzImage4,
							const GLdouble &imageSize);

	//----------------------------------------------------------------------------------

    // Privatised copy constructor and assignment operator
    TexturedPolygons (const TexturedPolygons &tp) {};
    TexturedPolygons &operator = (const TexturedPolygons &tp) {};
};
#endif

//----------------------------------------------------------------------------------
