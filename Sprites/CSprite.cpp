#include "CSprite.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "GraphicsObject_Sprite.h"

#include "Matrix.h"
#include "Vect.h"

CSprite::CSprite(std::string imgKey)
{
	spriteGraphObj = new GraphicsObject_Sprite(ModelManager::getModel("SpriteModel"), ShaderManager::getShader("SpriteShader"), ImageManager::getImage(imgKey), ImageManager::getImage(imgKey)->pImageRect);
	angle = 0.0f;
	centerX = ImageManager::getImage(imgKey)->pImageRect->width / 2;
	centerY = ImageManager::getImage(imgKey)->pImageRect->height / 2;
	scaleX = 1.0f;
	scaleY = 1.0f;
	posX = spriteGraphObj->origPosX;
	posY = spriteGraphObj->origPosY;

	Matrix world;
	Matrix scale;
	scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	//sprite should only rotate in Z
	Matrix rotZ;
	rotZ.set(ROT_Z, 0.0f);
	Matrix trans;
	trans.set(TRANS, posX, posY, 0.0f);

	world = scale * rotZ * trans;
	spriteGraphObj->SetWorld(world);
}

CSprite::~CSprite()
{
	delete spriteGraphObj;
	spriteGraphObj = nullptr;
}

float CSprite::getAngle() const
{
	return angle;
}

void CSprite::Render(Camera* cam)
{
	spriteGraphObj->Render(cam);
}

void CSprite::setAngle(float newAngle)
{
	angle = newAngle;

	//need to reset SRT matrices, as this is RESETTING the angle, not adding to/lessening it
	Matrix world;
	Matrix scale;
	scale.set(SCALE, scaleX, scaleY, 1.0f);
	//sprite should only rotate in Z
	Matrix rotZ;
	rotZ.set(ROT_Z, angle);
	Matrix trans;
	trans.set(TRANS, posX, posY, 0.0f);

	world = scale * rotZ * trans;
	spriteGraphObj->SetWorld(world);
}

void CSprite::setCenter(float offsetX, float offsetY)
{
	centerX = offsetX;
	centerY = offsetY;
}

void CSprite::setPosition(float newXPos, float newYPos)
{
	posX = newXPos;
	posY = newYPos;

	//need to reset SRT matrices, as this is RESETTING the center, not merely adding/subtracting from the old one
	Matrix world;
	Matrix scale;
	scale.set(SCALE, scaleX, scaleY, 1.0f);
	//sprite should only rotate in Z
	Matrix rotZ;
	rotZ.set(ROT_Z, angle);
	Matrix trans;
	trans.set(TRANS, posX, posY, 0.0f);

	world = scale * rotZ * trans;
	spriteGraphObj->SetWorld(world);
}

void CSprite::setScaleFactor(float newScaleX, float newScaleY)
{
	scaleX = newScaleX;
	scaleY = newScaleY;

	//need to reset SRT matrices, as this is RESETTING the scale, not merely adding/subtracting from the old one
	Matrix world;
	Matrix scale;
	scale.set(SCALE, scaleX, scaleY, 1.0f);
	//sprite should only rotate in Z
	Matrix rotZ;
	rotZ.set(ROT_Z, angle);
	Matrix trans;
	trans.set(TRANS, centerX, centerY, 0.0f);

	world = scale * rotZ * trans;
	spriteGraphObj->SetWorld(world);
}

void CSprite::setScalePixel(float newWidth, float newHeight)
{
	scaleX = (scaleX * newWidth) / spriteGraphObj->pImage->pImageRect->width;
	scaleY = (scaleY * newHeight) / spriteGraphObj->pImage->pImageRect->height;

	//need to reset SRT matrices, as this is RESETTING the scale, not merely adding/subtracting from the old one
	Matrix world;
	Matrix scale;
	scale.set(SCALE, scaleX, scaleY, 1.0f);
	//sprite should only rotate in Z
	Matrix rotZ;
	rotZ.set(ROT_Z, angle);
	Matrix trans;
	trans.set(TRANS, centerX, centerY, 0.0f);

	world = scale * rotZ * trans;
	spriteGraphObj->SetWorld(world);
}

float CSprite::getWidth() const
{
	return spriteGraphObj->pImage->pImageRect->width;
}

float CSprite::getHeight() const
{
	return spriteGraphObj->pImage->pImageRect->height;
}