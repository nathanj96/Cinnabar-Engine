#include "VisualizerAABBCommand.h"
#include "VisualizerAttorney.h"
#include "VisualizerCommandFactory.h"

VisualizerAABBCommand::VisualizerAABBCommand(const CollisionVolumeAABB& vol, const Vect& color) : aabb(vol), col(color)
{
};

void VisualizerAABBCommand::Execute()
{
	//calculate matrix to translate visualizer unit cube to world
	float scaleX = aabb.getMaxCorner().X() - aabb.getMinCorner().X();
	float scaleY = aabb.getMaxCorner().Y() - aabb.getMinCorner().Y();
	float scaleZ = aabb.getMaxCorner().Z() - aabb.getMinCorner().Z();
	Vect scaleVect = Vect(scaleX, scaleY, scaleZ);
	float transX = (aabb.getMinCorner().X() + aabb.getMaxCorner().X()) / 2;
	float transY = (aabb.getMinCorner().Y() + aabb.getMaxCorner().Y()) / 2;
	float transZ = (aabb.getMinCorner().Z() + aabb.getMaxCorner().Z()) / 2;
	Vect transVect = Vect(transX, transY, transZ);
	Matrix worldAABB = Matrix(IDENTITY) * Matrix(SCALE, scaleVect) * Matrix(TRANS, transVect);
	VisualizerAttorney::toAABBCommand::RenderAABB(worldAABB, col);
	VisualizerCommandFactory::recycleAABBCommand(this);
}

void VisualizerAABBCommand::SetAABB(const CollisionVolumeAABB& newAABB)
{
	aabb = newAABB;
}

void VisualizerAABBCommand::SetColor(const Vect& newColor)
{
	col = newColor;
}