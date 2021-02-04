#include "RegisterDraw2DCommand.h"
#include "DrawableAttorney.h"

RegisterDraw2DCommand::RegisterDraw2DCommand(Drawable* draw) : drawObj(draw)
{
};

void RegisterDraw2DCommand::Execute()
{
	DrawableAttorney::Registration2D::RegisterDrawable2D(drawObj);
}