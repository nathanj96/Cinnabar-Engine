#include "DeregisterDrawCommand.h"
#include "DrawableAttorney.h"

DeregisterDrawCommand::DeregisterDrawCommand(Drawable* draw) : drawObj(draw)
{
};

void DeregisterDrawCommand::Execute()
{
	DrawableAttorney::Registration::DeregisterDrawable(drawObj);
}