#include "DeregisterKeyReleasedCommand.h"
#include "Inputable.h"
#include "InputableAttorney.h"

DeregisterKeyReleasedCommand::DeregisterKeyReleasedCommand(Inputable* in, AZUL_KEY k) : inputObj(in), key(k)
{
};

void DeregisterKeyReleasedCommand::Execute()
{
	InputableAttorney::Registration::SceneKeyReleaseDeregistration(inputObj, key);
}