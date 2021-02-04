#include "VisualizerCommandFactory.h"
#include "VisualizerBSphereCommandObjectPool.h"
#include "VisualizerAABBCommandObjectPool.h"
#include "VisualizerOBBCommandObjectPool.h"

VisualizerCommandFactory* VisualizerCommandFactory::visualizerCommandFactoryInstance = nullptr;

void VisualizerCommandFactory::Initialize()
{
	Instance().bSphereCmdPool = new VisualizerBSphereCommandObjectPool();
	Instance().aabbCmdPool = new VisualizerAABBCommandObjectPool();
	Instance().obbCmdPool = new VisualizerOBBCommandObjectPool();
}

void VisualizerCommandFactory::Terminate()
{
	delete Instance().bSphereCmdPool;
	Instance().bSphereCmdPool = nullptr;
	delete Instance().aabbCmdPool;
	Instance().aabbCmdPool = nullptr;
	delete Instance().obbCmdPool;
	Instance().obbCmdPool = nullptr;
	delete visualizerCommandFactoryInstance;
	visualizerCommandFactoryInstance = nullptr;
}

VisualizerBSphereCommand* VisualizerCommandFactory::createBSphereCommand(const CollisionVolumeBSphere& bSph, const Vect& col)
{
	return Instance().bSphereCmdPool->getBSphereCommand(bSph, col);
}

void VisualizerCommandFactory::recycleBSphereCommand(VisualizerBSphereCommand* cmd)
{
	Instance().bSphereCmdPool->returnBSphereCommand(cmd);
}

VisualizerAABBCommand* VisualizerCommandFactory::createAABBCommand(const CollisionVolumeAABB& aabb, const Vect& col)
{
	return Instance().aabbCmdPool->getAABBCommand(aabb, col);
}

void VisualizerCommandFactory::recycleAABBCommand(VisualizerAABBCommand* cmd)
{
	Instance().aabbCmdPool->returnAABBCommand(cmd);
}

VisualizerOBBCommand* VisualizerCommandFactory::createOBBCommand(const CollisionVolumeOBB& obb, const Vect& col, const Matrix& world)
{
	return Instance().obbCmdPool->getOBBCommand(obb, col, world);
}

void VisualizerCommandFactory::recycleOBBCommand(VisualizerOBBCommand* cmd)
{
	Instance().obbCmdPool->returnOBBCommand(cmd);
}