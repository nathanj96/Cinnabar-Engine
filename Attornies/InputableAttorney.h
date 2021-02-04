#ifndef INPUTABLE_ATTORNEY
#define INPUTABLE_ATTORNEY

#include "Inputable.h"

class SingleKeyEventManager;
class RegisterKeyPressedCommand;
class DeregisterKeyPressedCommand;
class RegisterKeyReleasedCommand;
class DeregisterKeyReleasedCommand;

class InputableAttorney
{
	friend class SingleKeyEventManager;
private:
	static void keyPressed(Inputable* in, AZUL_KEY k)
	{
		in->KeyPressed(k);
	}
	static void keyReleased(Inputable* in, AZUL_KEY k)
	{
		in->KeyReleased(k);
	}
public:
	class Registration
	{
		friend class SingleKeyEventManager;
		friend class RegisterKeyPressedCommand;
		friend class DeregisterKeyPressedCommand;
		friend class RegisterKeyReleasedCommand;
		friend class DeregisterKeyReleasedCommand;
	private:
		static void setKeyPressListRef(Inputable* in, AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef)
		{
			in->setKeyPressListRef(k, newRef);
		}
		static void setKeyReleaseListRef(Inputable* in, AZUL_KEY k, SingleKeyEventManager::InputableListRef newRef)
		{
			in->setKeyReleaseListRef(k, newRef);
		}
		static void SceneKeyPressRegistration(Inputable* in, AZUL_KEY k)
		{
			in->SceneKeyPressRegistration(k);
		}
		static void SceneKeyReleaseRegistration(Inputable* in, AZUL_KEY k)
		{
			in->SceneKeyReleaseRegistration(k);
		}
		static void SceneKeyPressDeregistration(Inputable* in, AZUL_KEY k)
		{
			in->SceneKeyPressDeregistration(k);
		}
		static void SceneKeyReleaseDeregistration(Inputable* in, AZUL_KEY k)
		{
			in->SceneKeyReleaseDeregistration(k);
		}
	};
};

#endif INPUTABLE_ATTORNEY