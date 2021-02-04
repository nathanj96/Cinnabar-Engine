#ifndef SPRITE_TEST
#define SPRITE_TEST

#include "Drawable.h"
#include "Updatable.h"

class CSprite;
class SpriteFont;
class SpriteString;

class SpriteTest : public Drawable, public Updatable
{
public:
	SpriteTest();
	SpriteTest(const SpriteTest&) = default;
	SpriteTest& operator=(const SpriteTest&) = default;
	~SpriteTest();

	CSprite* testSpr;
	virtual void Draw2D();
	virtual void Update();
	SpriteFont* fontTest;
	SpriteString* stringTest;
};

#endif SPRITE_TEST