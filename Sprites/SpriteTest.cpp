#include "SpriteTest.h"
#include "CSprite.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "Image.h"
#include "SpriteFont.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"

SpriteTest::SpriteTest()
{
	testSpr = new CSprite("StitchImg");
	testSpr->setAngle(3.14159f);
	testSpr->setScaleFactor(0.7f, 0.7f);
	testSpr->setPosition(700, 500);
	testSpr->setCenter(500, 500);
	fontTest = SpriteFontManager::getSpriteFont("TestFont");
	//stringTest = new SpriteString(fontTest, "Abcdefghijk", 34, 34);
	SubmitRegisterDrawable2DCommand();
	SubmitRegisterUpdatableCommand();
}

SpriteTest::~SpriteTest()
{
	delete testSpr;
	testSpr = nullptr;
	//delete stringTest;
	//stringTest = nullptr;
	SubmitDeregisterDrawable2DCommand();
	SubmitDeregisterUpdatableCommand();
}

void SpriteTest::Update()
{
	testSpr->setAngle(testSpr->getAngle() + 0.1f);
}

void SpriteTest::Draw2D()
{
	testSpr->Render(SceneManager::getCurrent2DCamera());
	//stringTest->Render();
}