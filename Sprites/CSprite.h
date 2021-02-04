//Wrapper class for 2D sprites

#ifndef C_SPRITE
#define C_SPRITE

class GraphicsObject_Sprite;
class Camera;
class CSpriteAttorney;

#include <string>
using namespace std;

class CSprite
{
	friend class CSpriteAttorney;
private:

	/** \brief	The angle of the sprite, in radians. */
	float angle;
	/** \brief	The X position of the sprite's pivot point. */
	float centerX;
	/** \brief	The Y position of the sprite's pivot point. */
	float centerY;
	GraphicsObject_Sprite* spriteGraphObj;
	/** \brief	The sprite's X scale. */
	float scaleX;
	/** \brief	The sprite's Y scale */
	float scaleY;
	/** \brief	The sprite's X position in <b>2D</b> space. */
	float posX;
	/** \brief	The sprite's Y position in <b>2D</b> space. */
	float posY;
	float getWidth() const;
	float getHeight() const;
public:
	//don't enable creating an empty sprite
	CSprite() = delete;
	CSprite(const CSprite&) = default;
	CSprite& operator=(const CSprite&) = default;
	~CSprite();

	/**********************************************************************************************//**
	 * \fn	CSprite::CSprite(std::string imgKey);
	 * \ingroup CSPRITEMETHODS
	 * \brief	Constructs a sprite using the Image associated with imgKey.
	 *
	 * \param 	imgKey	The image key.
	 **************************************************************************************************/

	CSprite(std::string imgKey);
	float getAngle() const;

	void Render(Camera* cam);

	/**********************************************************************************************//**
	 * \fn	void CSprite::setAngle(float newAngle);
	 * \ingroup CSPRITEMETHODS
	 * \brief	Sets a new angle for the CSprite
	 *
	 * \param 	newAngle	The new angle, in radians.
	 **************************************************************************************************/

	void setAngle(float newAngle);

	/**********************************************************************************************//**
	 * \fn	void CSprite::setCenter(float offsetX, float offsetY);
	 * \ingroup CSPRITEMETHODS
	 * \brief	Sets a new pivot point for the CSprite.
	 *
	 * \param 	offsetX	The new pivot point x coordinate.
	 * \param 	offsetY	The new pivot point y coordinate.
	 **************************************************************************************************/

	void setCenter(float offsetX, float offsetY);
	void setPosition(float newXPos, float newYPos);

	/**********************************************************************************************//**
	 * \fn	void CSprite::setScaleFactor(float newScaleX, float newScaleY);
	 * \ingroup CSPRITEMETHODS
	 * \brief	Changes scaleX and scaleY, then calculcates the sprite's new world matrix accordingly.
	 *
	 * \param 	newScaleX	The new scale x coordinate.
	 * \param 	newScaleY	The new scale y coordinate.
	 **************************************************************************************************/

	void setScaleFactor(float newScaleX, float newScaleY);

	/**********************************************************************************************//**
	 * \fn	void CSprite::setScalePixel(float newWidth, float newHeight);
	 * \ingroup CSPRITEMETHODS
	 * \brief	Determines the scale factors necessary for the sprite to be newWidth x newHeight pixels,
	 * 			then calculates the sprite's new world matrix accordingly.
	 *
	 * \param 	newWidth 	The new width, in pixels.
	 * \param 	newHeight	The new height, in pixels.
	 **************************************************************************************************/

	void setScalePixel(float newWidth, float newHeight);
};

#endif C_SPRITE