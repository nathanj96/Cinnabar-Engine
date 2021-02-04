#include "RegisterDrawCommand.h"
#include "DrawableAttorney.h"

RegisterDrawCommand::RegisterDrawCommand(Drawable* draw) : drawObj(draw)
{
};

void RegisterDrawCommand::Execute()
{
	DrawableAttorney::Registration::RegisterDrawable(drawObj);
}