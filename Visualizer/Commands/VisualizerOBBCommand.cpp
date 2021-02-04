#include "VisualizerOBBCommand.h"
#include "VisualizerCommandFactory.h"
#include "VisualizerAttorney.h"

VisualizerOBBCommand::VisualizerOBBCommand(const CollisionVolumeOBB& vol, const Vect& color, const Matrix& worldMat) : obb(vol), col(color), world(worldMat)
{
};

void VisualizerOBBCommand::Execute()
{
	float scaleX = obb.getMaxLocal().X() - obb.getMinLocal().X();
	float scaleY = obb.getMaxLocal().Y() - obb.getMinLocal().Y();
	float scaleZ = obb.getMaxLocal().Z() - obb.getMinLocal().Z();
	Vect scaleVect = Vect(scaleX, scaleY, scaleZ);
	float transX = (obb.getMinLocal().X() + obb.getMaxLocal().X()) / 2;
	float transY = (obb.getMinLocal().Y() + obb.getMaxLocal().Y()) / 2;
	float transZ = (obb.getMinLocal().Z() + obb.getMaxLocal().Z()) / 2;
	Vect transVect = Vect(transX, transY, transZ);
	Matrix localOBB = Matrix(IDENTITY) * Matrix(SCALE, scaleVect) * Matrix(TRANS, transVect);
	Matrix worldOBB = localOBB * world;
	VisualizerAttorney::toOBBCommand::RenderOBB(worldOBB, col);
	VisualizerCommandFactory::recycleOBBCommand(this);
}

void VisualizerOBBCommand::SetOBB(const CollisionVolumeOBB& newOBB)
{
	obb = newOBB;
}

void VisualizerOBBCommand::SetColor(const Vect& newColor)
{
	col = newColor;
}

void VisualizerOBBCommand::SetWorld(const Matrix& newWorld)
{
	world = newWorld;
}