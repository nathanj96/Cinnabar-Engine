#include "RegisterKeyReleasedCommand.h"
#include "Inputable.h"
#include "InputableAttorney.h"

RegisterKeyReleasedCommand::RegisterKeyReleasedCommand(Inputable* in, AZUL_KEY k) : inputObj(in), key(k)
{
};

void RegisterKeyReleasedCommand::Execute()
{
	InputableAttorney::Registration::SceneKeyReleaseRegistration(inputObj, key);
}