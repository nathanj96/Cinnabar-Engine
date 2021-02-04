#include "../CinnabarEngine.h"
#include "TankGameManager.h"

/**********************************************************************************************//**
 * \fn	void CinnabarEngine::gameInitialize()
 *
 * \brief	User-defined. Functionality for initializing a specific game. Kept in a separate file from
 * 			the engine initialization code so the user can't access/modify it.
 **************************************************************************************************/

void CinnabarEngine::gameInitialize()
{
	// Game Window Device setup
	CinnabarEngine::SetWindowName("Matrices and Movement");
	CinnabarEngine::SetWindowSize(800, 600);
	CinnabarEngine::setClearColor(0.4f, 0.4f, 0.8f, 1.0f);
    TankGameManager::TankGameInitialize();
}