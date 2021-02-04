#ifndef C_SOUND_ASSET_MANAGER_ATTORNEY
#define C_SOUND_ASSET_MANAGER_ATTORNEY

class CinnabarEngine;

#include "CSoundAssetManager.h"

class CSoundAssetManagerAttorney
{
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		CSoundAssetManager::Terminate();
	}
};

#endif C_SOUND_ASSET_MANAGER_ATTORNEY