#include "Collidable.h"

#include "RegistrationCommandBase.h"
#include "RegisterCollidableCommand.h"
#include "DeregisterCollidableCommand.h"
#include "VisualizerCommandBroker.h"
#include "VisualizerCommandFactory.h"
#include "VisualizerCommandBase.h"
#include "VisualizerBSphereCommand.h"
#include "TerrainModel.h"
#include "Model.h"

#include "CollisionVolumeBase.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

#include "CMathTools.h"
#include "Visualizer.h"
#include "Colors.h"

Collidable::Collidable()
{
	collidableRegState = RegistrationState::CURRENTLY_DEREGISTERED;
	collidableRegistrationCmdPtr = new RegisterCollidableCommand(this);
	collidableDeregistrationCmdPtr = new DeregisterCollidableCommand(this);
	pColModel = nullptr;
	colVolume = nullptr;
}

void Collidable::SubmitRegisterCollidableCommand()
{
	assert(collidableRegState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::toCollidable::submitCollidableCommand(collidableRegistrationCmdPtr);
	collidableRegState = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitDeregisterCollidableCommand()
{
	assert(collidableRegState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::toCollidable::submitCollidableCommand(collidableDeregistrationCmdPtr);
	collidableRegState = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::RegisterCollidable()
{
	assert(collidableRegState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::toCollidable::registerCollidable(myID, this);
	collidableRegState = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::DeregisterCollidable()
{
	assert(collidableRegState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::toCollidable::deregisterCollidable(myID, this);
	collidableRegState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::setCollidableObjRef(CollidableGroup::CollidableCollectionRef newRef)
{
	collidableObjRef = newRef;
}

const CollidableGroup::CollidableCollectionRef& Collidable::getRef() const
{
	return collidableObjRef;
}

const CollisionVolumeBase& Collidable::GetCollisionVolume() const
{
	return *colVolume;
}

const CollisionVolumeBSphere& Collidable::GetPartitionSphere() const
{
	return partitionSphere;
}

void Collidable::SetColliderModel(Model* mod, Collidable::VolumeType volType)
{
	pColModel = mod;
	//PLACEHOLDER FOR NOW
	switch (volType)
	{
	case(BSphere):
	{
		colVolume = new CollisionVolumeBSphere();
		break;
	}
	case(AABB):
	{
		colVolume = new CollisionVolumeAABB(mod);
		break;
	}
	case(OBB):
	{
		colVolume = new CollisionVolumeOBB(mod);
		break;
	}
	}
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	colVolume->ComputeData(pColModel, mat);
	//always update BSphere for partitioning purposes
	partitionSphere.ComputeData(pColModel, mat);
}

void Collidable::findTerrainCells(TerrainModel* terr)
{
	//find min/max coords of the area covered by the collidable's BSphere
	float rad = GetPartitionSphere().GetRadius();
	Vect min = GetPartitionSphere().GetCenter() - Vect(rad, rad, rad);
	Vect max = GetPartitionSphere().GetCenter() + Vect(rad, rad, rad);
	//debug
	//Visualizer::ShowTerrainCell(terr, min.X(), min.Z(), Colors::Yellow);
	//Visualizer::ShowTerrainCell(terr, max.X(), max.Z(), Colors::Yellow);
	//
	//the next 2 variables comprise the distance between the min/max coords in each direction
	float TRAXDim = abs(rad) * 2.0f;
	float TRAZDim = abs(rad) * 2.0f;
	//use these to figure out how many rows/columns to iterate through
	int rows = (int)(round(TRAXDim / terr->getCellDim()));
	int cols = (int)(round(TRAZDim / terr->getCellDim()));
	float currZ = min.Z();
	float currX = min.X();
	for (int i = 0; i <= cols; i++)
	{
		//each time there's a column change, start at the same point in the row
		currX = min.X();
		for (int j = 0; j <= rows; j++)
		{
			TerrainModel::CellMinMaxPair cellToShow = terr->getCellAt2DCoords(currX, currZ);
			CollisionVolumeAABB vol;
			//this function computes AABB data without having to iterate through every vertex in a model, since we already
			//have the min/max points
			vol.ComputeDataTerrain(cellToShow.min, cellToShow.max);
			//tiered collision test. Only BSphere/precise model tests are relevant here
			if (CMathTools::Intersect(GetPartitionSphere(), vol))
			{
				if (CMathTools::Intersect(GetCollisionVolume(), vol))
				{
					Visualizer::ShowAABB(vol, Colors::Red);
				}
				else
				{
					Visualizer::ShowAABB(vol, Colors::Yellow);
				}
			}
			else
			{
				Visualizer::ShowAABB(vol, Colors::Green);
			}
			currX += terr->getCellDim();
		}
		currZ += terr->getCellDim();
	}
}

void Collidable::DeleteColVol()
{
	delete colVolume;
	colVolume = nullptr;
}

Collidable::~Collidable()
{
	delete collidableRegistrationCmdPtr;
	collidableRegistrationCmdPtr = nullptr;
	delete collidableDeregistrationCmdPtr;
	collidableDeregistrationCmdPtr = nullptr;
	delete colVolume;
	colVolume = nullptr;
}