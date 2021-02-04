#ifndef INPUTABLE
#define INPUTABLE

#include "Keyboard.h"
#include "RegistrationState.h"
//these are defined in their own classes to give them constructors, since there's going to be a variable amount of them
#include "KeyboardPressRegistrationData.h"
#include "KeyboardReleaseRegistrationData.h"
#include "SingleKeyEventManager.h"
#include <map>

class RegisterKeyPressedCommand;
class DeregisterKeyPressedCommand;
class RegisterKeyReleasedCommand;
class DeregisterKeyReleaseCommand;
class InputableAttorney;

class Inputable
{
	friend class InputableAttorney;
public:
	enum EVENT_TYPE
	{
		KEY_PRESS,
		KEY_RELEASE,
	};
private:
	using KeyPressRegistrationMap = std::map<AZUL_KEY, KeyboardPressRegistrationData*>;
	KeyPressRegistrationMap pressRegisteredKeys;
	using KeyReleaseRegistrationMap = std::map<AZUL_KEY, KeyboardReleaseRegistrationData*>;
	KeyReleaseRegistrationMap releaseRegisteredKeys;
	//callbacks for key input events (define in each derived class)

	/**********************************************************************************************//**
	 * \fn	virtual void Inputable::KeyPressed(AZUL_KEY k)
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup INPUTABLEMETHODS
	 * \brief	Callback when a key is pressed.
	 * 			
	 * \note As is, this function will fire every time <b>any</b> any registered key is pressed. Determining
	 * 		 which specific key was pressed, and therefore what code to execute, requires conditionals:
	 * 		 
	 *		\code
	 *			virtual void KeyPressed(AZUL_KEY k)
	 *			{
	 *				switch(k)
	 *				{
	 *				case(AZUL_KEY::KEY_T)
	 *				{
	 *					//do something
	 *					break;
	 *				}
	 *				case(AZUL_KEY::KEY_S)
	 *				{
	 *					//do something else
	 *					break;
	 *				}
	 *				case(AZUL_KEY::KEY_E)
	 *				{
	 *					//do something else
	 *					break;
	 *				}
	 *				}
	 *			}
	 *		\endcode
	 *				
	 * \note Cinnabar Engine currently does not support key held events. The effect can be achieved, however,
	 * 		 by checking if Keyboard::GetKeyState(AZUL_KEY k) == true every tick.
	 *					 
	 **************************************************************************************************/

	virtual void KeyPressed(AZUL_KEY k)
	{
		UNREFERENCED_PARAMETER(k);
	};

	/**********************************************************************************************//**
	 * \fn	virtual void Inputable::KeyReleased(AZUL_KEY k)
	 * \ingroup GAMELOOPEVENTS
	 * \ingroup INPUTABLEMETHODS
	 * \brief	Callback when a key is released.
	 *
	 * \note As is, this function will fire every time <b>any</b> any registered key is released. Determining
	 * 		 which specific key was released, and therefore what code to execute, requires conditionals:
	 *
	 *		\code
	 *			virtual void KeyReleased(AZUL_KEY k)
	 *			{
	 *				switch(k)
	 *				{
	 *				case(AZUL_KEY::KEY_T)
	 *				{
	 *					//do something
	 *					break;
	 *				}
	 *				case(AZUL_KEY::KEY_S)
	 *				{
	 *					//do something else
	 *					break;
	 *				}
	 *				case(AZUL_KEY::KEY_E)
	 *				{
	 *					//do something else
	 *					break;
	 *				}
	 *				}
	 *			}
	 *		\endcode
	 *
	 **************************************************************************************************/
	virtual void KeyReleased(AZUL_KEY k)
	{
		UNREFERENCED_PARAMETER(k);
	};

	//for use by engine only
	void setKeyPressListRef(AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef);
	void setKeyReleaseListRef(AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef);

	//process registration commands
	void SceneKeyPressRegistration(AZUL_KEY k);
	void SceneKeyReleaseRegistration(AZUL_KEY k);
	void SceneKeyPressDeregistration(AZUL_KEY k);
	void SceneKeyReleaseDeregistration(AZUL_KEY k);
protected:
	//command submission

	/**********************************************************************************************//**
	 * \fn	void Inputable::SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e);
	 * \ingroup INPUTABLEREGISTRATION
	 * \brief	On the frame after this function is called, the key k will be registered to check for either
	 * 			key presses or key releases every tick.
	 *
	 * \param 	k	An AZUL_KEY to process.
	 * \param 	e	An EVENT_TYPE to process, either KEY_PRESS or KEY_RELEASE.
	 **************************************************************************************************/

	void SubmitKeyRegistration(AZUL_KEY k, EVENT_TYPE e);

	/**********************************************************************************************//**
	* \fn	void Inputable::SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e);
	* \ingroup INPUTABLEREGISTRATION
	* \brief	On the frame after this function is called, the key k will no longer check for either
	* 			key presses or key releases every tick.
	*
	* \param 	k	An AZUL_KEY to process.
	* \param 	e	An EVENT_TYPE to process, either KEY_PRESS or KEY_RELEASE.
	 **************************************************************************************************/
	void SubmitKeyDeregistration(AZUL_KEY k, EVENT_TYPE e);
public:
	Inputable() = default;
	Inputable(const Inputable&) = default;
	Inputable& operator=(const Inputable&) = default;
	virtual ~Inputable();

	SingleKeyEventManager::InputableListRef getKeyPressListRef(AZUL_KEY k);
	SingleKeyEventManager::InputableListRef getKeyReleaseListRef(AZUL_KEY k);

};

#endif INPUTABLE