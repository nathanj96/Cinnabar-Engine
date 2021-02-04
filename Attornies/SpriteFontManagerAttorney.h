#ifndef SPRITE_FONT_MANAGER_ATTORNEY
#define SPRITE_FONT_MANAGER_ATTORNEY

#include "SpriteFontManager.h"

class CinnabarEngine;

class SpriteFontManagerAttorney
{
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		SpriteFontManager::Terminate();
	}
};

#endif SPRITE_FONT_MANAGER_ATTORNEY