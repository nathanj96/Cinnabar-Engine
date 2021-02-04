#include "RegisterKeyPressedCommand.h"
#include "Inputable.h"
#include "InputableAttorney.h"

RegisterKeyPressedCommand::RegisterKeyPressedCommand(Inputable* in, AZUL_KEY k) : inputObj(in), key(k)
{
};

void RegisterKeyPressedCommand::Execute()
{
	InputableAttorney::Registration::SceneKeyPressRegistration(inputObj, key);
}