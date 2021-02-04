#ifndef CINNABAR_ENGINE_ATTORNEY
#define CINNABAR_ENGINE_ATTORNEY

class FreezeTime;

#include "../CinnabarEngine.h"

class CinnabarEngineAttorney
{
	friend class FreezeTime;
private:
	static float getTimeInSeconds()
	{
		return CinnabarEngine::Instance().getTimeInSeconds();
	}
};

#endif CINNABAR_ENGINE_ATTORNEY