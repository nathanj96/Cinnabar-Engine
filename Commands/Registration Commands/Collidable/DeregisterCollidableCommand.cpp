#include "DeregisterCollidableCommand.h"
#include "CollidableAttorney.h"

DeregisterCollidableCommand::DeregisterCollidableCommand(Collidable* col) : colObj(col)
{
};

void DeregisterCollidableCommand::Execute()
{
	CollidableAttorney::Registration::DeregisterCollidable(colObj);
}

