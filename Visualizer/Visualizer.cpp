#include "Visualizer.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "TerrainModel.h"
#include "CSoundGeometry.h"

#include "VisualizerCommandFactory.h"
#include "VisualizerCommandBase.h"
#include "VisualizerBSphereCommand.h"
#include "VisualizerAABBCommand.h"
#include "VisualizerOBBCommand.h"

#include "CollisionVolumeOBB.h"

Visualizer* Visualizer::visualizerInstance = nullptr;
Vect Visualizer::defaultColor = Vect(0, 0, 255);

void Visualizer::Initialize()
{
	Instance().WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::getModel("ModelSphere"), ShaderManager::getShader("ShaderObject_constantColor"), defaultColor);
	Instance().WFUnitCube = new GraphicsObject_WireframeConstantColor(ModelManager::getModel("ModelBox_WF"), ShaderManager::getShader("ShaderObject_constantColor"), defaultColor);
}

void Visualizer::Terminate()
{
	delete Instance().WFUnitSphere;
	Instance().WFUnitSphere = nullptr;
	delete Instance().WFUnitCube;
	Instance().WFUnitCube = nullptr;
	delete visualizerInstance;
	visualizerInstance = nullptr;
}

void Visualizer::privRenderBSphere(Matrix& S, const Vect& col)
{
	Instance().WFUnitSphere->SetWorld(S);
	Instance().WFUnitSphere->SetColor(col);
	Instance().WFUnitSphere->Render(SceneManager::getCurrentCamera());
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	SceneAttorney::toVisualizer::submitVisualizerCommand(VisualizerCommandFactory::createBSphereCommand(S, col));
}

void Visualizer::privRenderAABB(Matrix& S, const Vect& col)
{
	//calculate the matrix outside of here...
	Instance().WFUnitCube->SetWorld(S);
	Instance().WFUnitCube->SetColor(col);
	Instance().WFUnitCube->Render(SceneManager::getCurrentCamera());
}

void Visualizer::privRenderOBB(Matrix& S, const Vect col)
{
	//same process as for the AABB, but separate function to avoid confusion
	Instance().WFUnitCube->SetWorld(S);
	Instance().WFUnitCube->SetColor(col);
	Instance().WFUnitCube->Render(SceneManager::getCurrentCamera());
}

void Visualizer::ShowCollisionVolume(const CollisionVolumeBase& vol, const Vect& col)
{
	vol.DebugView(col);
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& a, const Vect& col)
{
	SceneAttorney::toVisualizer::submitVisualizerCommand(VisualizerCommandFactory::createAABBCommand(a, col));
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& a, const Vect& col, const Matrix& world)
{
	SceneAttorney::toVisualizer::submitVisualizerCommand(VisualizerCommandFactory::createOBBCommand(a, col, world));
}

void Visualizer::ShowTerrainCollision(TerrainModel* terr, int numCells, const Vect& col)
{
	TerrainModel::CellMinMaxPair* cellMinMaxes = terr->getCellMinMaxCoords();
	CollisionVolumeAABB vol;
	for (int i = 0; i < numCells; i++)
	{
		vol.ComputeDataTerrain(cellMinMaxes[i].min, cellMinMaxes[i].max);
		SceneAttorney::toVisualizer::submitVisualizerCommand(VisualizerCommandFactory::createAABBCommand(vol, col));
	}
}

void Visualizer::ShowTerrainCell(TerrainModel* terr, float xCoord, float zCoord, const Vect& col)
{
	TerrainModel::CellMinMaxPair cellToShow = terr->getCellAt2DCoords(xCoord, zCoord);
	CollisionVolumeAABB vol;
	vol.ComputeDataTerrain(cellToShow.min, cellToShow.max);
	//submit command
	Visualizer::ShowAABB(vol, col);
}

void Visualizer::ShowCSoundGeometry(CSoundGeometry* geo, const Vect& col, const Matrix& world)
{
	CollisionVolumeAABB vol;
	Vect min;
	Vect max;
	geo->ComputePolysMinMax(&min, &max, world);
	vol.ComputeDataSoundGeometry(min, max);
	SceneAttorney::toVisualizer::submitVisualizerCommand(VisualizerCommandFactory::createAABBCommand(vol, col));
}

void Visualizer::ShowLine(const Vect& top, const Vect& bottom, const Vect& col)
{
	CollisionVolumeAABB vol;
	vol.ComputeDataTerrain(bottom, top);
	Visualizer::ShowAABB(vol, col);
}