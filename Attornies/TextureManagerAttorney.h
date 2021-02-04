#ifndef TEXTURE_MANAGER_ATTORNEY
#define TEXTURE_MANAGER_ATTORNEY

class CinnabarEngine;

#include "TextureManager.h"

class TextureManagerAttorney
{
	//giving it access to Terminate()
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		TextureManager::Terminate();
	}
};

#endif TEXTURE_MANAGER_ATTORNEY