#include "DeregisterDraw2DCommand.h"
#include "DrawableAttorney.h"

DeregisterDraw2DCommand::DeregisterDraw2DCommand(Drawable* draw) : drawObj(draw)
{
};

void DeregisterDraw2DCommand::Execute()
{
	DrawableAttorney::Registration2D::DeregisterDrawable2D(drawObj);
}