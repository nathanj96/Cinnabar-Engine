#include "../CinnabarEngine.h"
#include "TankGameManager.h"

/**********************************************************************************************//**
 * \fn	void CinnabarEngine::gameEnd()
 *
 * \brief	User-defined. Functionality for closing a specific game. Kept in a separate file from
 * 			the engine termination code so the user can't access/modify it.
 **************************************************************************************************/

void CinnabarEngine::gameEnd()
{
    TankGameManager::TankGameEnd();
}