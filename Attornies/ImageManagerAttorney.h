#ifndef IMAGE_MANAGER_ATTORNEY
#define IMAGE_MANAGER_ATTORNEY

#include "ImageManager.h"

class CinnabarEngine;

class ImageManagerAttorney
{
	//giving it access to Terminate()
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		ImageManager::Terminate();
	}
};

#endif IMAGE_MANAGER_ATTORNEY