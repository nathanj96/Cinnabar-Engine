#ifndef C_SPRITE_ATTORNEY
#define C_SPRITE_ATTORNEY

#include "CSprite.h"

class SpriteString;

class CSpriteAttorney
{
	friend class SpriteString;
private:
	static float GetWidth(CSprite* spr)
	{
		return spr->getWidth();
	}
	static float GetHeight(CSprite* spr)
	{
		return spr->getHeight();
	}
};

#endif C_SPRITE_ATTORNEY
