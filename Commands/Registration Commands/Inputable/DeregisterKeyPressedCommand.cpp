#include "DeregisterKeyPressedCommand.h"
#include "Inputable.h"
#include "InputableAttorney.h"

DeregisterKeyPressedCommand::DeregisterKeyPressedCommand(Inputable* in, AZUL_KEY k) : inputObj(in), key(k)
{
};

void DeregisterKeyPressedCommand::Execute()
{
	InputableAttorney::Registration::SceneKeyPressDeregistration(inputObj, key);
}