//Manager for all single-key input managers

#ifndef KEYBOARD_EVENT_MANAGER
#define KEYBOARD_EVENT_MANAGER

//forward declaration
class SingleKeyEventManager;

#include <Keyboard.h>
#include <map>
//for EVENT_TYPE enum
#include "Inputable.h"

class KeyboardEventManager
{
private:
	using SingleKeyMgrMap = std::map<AZUL_KEY, SingleKeyEventManager*>;
	SingleKeyMgrMap singleKeyMgrs;
public:
	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager&) = default;
	KeyboardEventManager& operator=(const KeyboardEventManager&) = default;
	~KeyboardEventManager();

	void DeregisterKeyPress(Inputable* in, AZUL_KEY k);
	void DeregisterKeyRelease(Inputable* in, AZUL_KEY k);

	/**********************************************************************************************//**
	 * \fn	void KeyboardEventManager::ProcessKeyEvents();
	 * \ingroup SCENEUPDATE
	 * \brief	Processes all key input and release checks necessary for the frame.
	 **************************************************************************************************/

	void ProcessKeyEvents();
	void RegisterKeyPress(Inputable* in, AZUL_KEY k);
	void RegisterKeyRelease(Inputable* in, AZUL_KEY k);
};

#endif KEYBOARD_EVENT_MANAGER