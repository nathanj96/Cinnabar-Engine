#include "SpriteString.h"
#include "CSprite.h"
#include "CSpriteAttorney.h"
#include "SceneManager.h"

SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y) : glyphs(0, nullptr)
{
	width = 0;
	sfont = sf;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		glyphs.push_back(sfont->GetGlyph(s[i]));
		width += (int)CSpriteAttorney::GetWidth(sfont->GetGlyph(s[i]));
	}
	height = (int)CSpriteAttorney::GetHeight(sfont->GetGlyph(s[0]));
	posx = x;
	posy = y;
}

SpriteString::SpriteString(SpriteFont* sf)
{
	width = 0;
	height = 0;
	posx = 0;
	posy = 0;
	sfont = sf;
}

int SpriteString::getHeight() const
{
	return height;
}

int SpriteString::getWidth() const
{
	return width;
}

void SpriteString::Render()
{
	float curX = (float)posx;
	float curY = (float)posy;
	for (unsigned int i = 0; i < glyphs.size(); i++)
	{
		glyphs[i]->setPosition(curX, curY);
		curX += CSpriteAttorney::GetWidth(glyphs[i]);
		glyphs[i]->Render(SceneManager::getCurrent2DCamera());
	}
}

void SpriteString::Set(int x, int y)
{
	posx = x;
	posy = y;
}

void SpriteString::Set(SpriteFont* sf, std::string s, int x, int y)
{
	width = 0;
	sfont = sf;
	//need to wipe out old glyphs and replace w/ones from new string
	glyphs.clear();
	for (unsigned int i = 0; i < s.size(); i++)
	{
		glyphs.push_back(sfont->GetGlyph(s[i]));
		width += (int)CSpriteAttorney::GetWidth(sfont->GetGlyph(s[i]));
	}
	height = (int)CSpriteAttorney::GetHeight(sfont->GetGlyph(s[0]));
	posx = x;
	posy = y;
}