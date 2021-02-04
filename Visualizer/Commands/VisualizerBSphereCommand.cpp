#include "VisualizerBSphereCommand.h"
#include "VisualizerAttorney.h"
#include "VisualizerCommandFactory.h"

VisualizerBSphereCommand::VisualizerBSphereCommand(const CollisionVolumeBSphere& sph, const Vect& color) : BSph(sph), col(color)
{
};

void VisualizerBSphereCommand::Execute()
{
	Vect vBSSize = BSph.GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = BSph.GetCenter();
	Matrix worldBS = Matrix(IDENTITY) * Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos);
	//access granted to this command class only
	VisualizerAttorney::toBSphereCommand::RenderBSphere(worldBS, col);
	VisualizerCommandFactory::recycleBSphereCommand(this);
}

void VisualizerBSphereCommand::SetBSphere(const CollisionVolumeBSphere& newSphere)
{
	BSph = newSphere;
}

void VisualizerBSphereCommand::SetColor(const Vect& newColor)
{
	col = newColor;
}