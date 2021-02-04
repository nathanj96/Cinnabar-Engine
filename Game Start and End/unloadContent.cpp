//unload game resources

#include "../CinnabarEngine.h"
#include "SceneManagerAttorney.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "ImageManagerAttorney.h"
#include "VisualizerCommandFactoryAttorney.h"
#include "ScreenLogAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "BulletFactory.h"
#include "PlayerManagerAttorney.h"
#include "TerrainModelManagerAttorney.h"
#include "CAudioManagerAttorney.h"
#include "CSoundAssetManagerAttorney.h"
#include "GameRegistrationManagerAttorney.h"

/**********************************************************************************************//**
 * \fn	void CinnabarEngine::UnLoadContent()
 *
 * \brief	User-defined. Unloads content loaded in CinnabarEngine::LoadResources(). Kept in a separate file from
 * 			the engine termination code so the user can't access/modify it.
 **************************************************************************************************/

void CinnabarEngine::UnLoadContent()
{
	SceneManagerAttorney::Engine::Terminate();
	ShaderManagerAttorney::Terminate();
	TextureManagerAttorney::Terminate();
	ModelManagerAttorney::Terminate();
	TimeManagerAttorney::Terminate();
	ImageManagerAttorney::Terminate();
	TerrainModelManagerAttorney::Terminate();
	VisualizerCommandFactoryAttorney::Terminate();
	VisualizerAttorney::GameLoop::Terminate();
	ScreenLogAttorney::GameLoop::Terminate();
	SpriteFontManagerAttorney::Terminate();
	CSoundAssetManagerAttorney::Terminate();
	CAudioManagerAttorney::gameLoop::Terminate();

	GameRegistrationManagerAttorney::GameLoop::Terminate();
	//terminate Factories
	BulletFactory::Terminate();
	//for demo
	PlayerManagerAttorney::toEngine::Terminate();
	gameEnd();
}
