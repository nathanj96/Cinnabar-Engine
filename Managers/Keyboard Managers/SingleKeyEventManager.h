//Manages the key pressed/released state of ONE key. A collection of these is managed by the KeyboardEventManager
//class to control keyboard input as a whole.

#ifndef SINGLE_KEY_EVENT_MANAGER
#define SINGLE_KEY_EVENT_MANAGER

class Inputable;

#include "Keyboard.h"
#include <list>

//for debug purposes
#include <string>
using namespace std;

class SingleKeyEventManager
{
private:
	//key corresponding to this manager
	AZUL_KEY key;
	using InputableList = std::list<Inputable*>;
	InputableList keyPressedList;
	InputableList keyReleasedList;
	//need to compare this to its current state to determine if a key press/release occurred
	bool keyPrevFrameState;
public:
	//force to assign the key on construction
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager& operator=(const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() = default;

	using InputableListRef = InputableList::iterator;
	void DeregisterKeyPress(Inputable* in);
	void DeregisterKeyRelease(Inputable* in);
	void ProcessKeyEvent();
	void RegisterKeyPress(Inputable* in);
	void RegisterKeyRelease(Inputable* in);
	SingleKeyEventManager(AZUL_KEY k);
	//debug function
	std::string getKeyName(AZUL_KEY k) const;
};

#endif SINGLE_KEY_EVENT_MANAGER