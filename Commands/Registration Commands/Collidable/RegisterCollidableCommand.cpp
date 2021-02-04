#include "RegisterCollidableCommand.h"
#include "CollidableAttorney.h"

RegisterCollidableCommand::RegisterCollidableCommand(Collidable* col) : colObj(col)
{
};

void RegisterCollidableCommand::Execute()
{
	CollidableAttorney::Registration::RegisterCollidable(colObj);
}

