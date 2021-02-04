#ifndef VISUALIZER_COMMAND_FACTORY
#define VISUALIZER_COMMAND_FACTORY

//maintains creation/destruction of visualizer commands for (eventually) ALL visualizer bounding volume types

#include "CollisionVolumeBSphere.h"
#include "Vect.h"

class VisualizerBSphereCommand;
class VisualizerBSphereCommandObjectPool;
class VisualizerAABBCommand;
class VisualizerAABBCommandObjectPool;
class VisualizerOBBCommand;
class VisualizerOBBCommandObjectPool;
class VisualizerCommandFactoryAttorney;

class VisualizerCommandFactory
{
	friend class VisualizerCommandFactoryAttorney;
private:
	//singleton
	static VisualizerCommandFactory* visualizerCommandFactoryInstance;

	VisualizerCommandFactory() = default;
	VisualizerCommandFactory(const VisualizerCommandFactory&) = delete;
	VisualizerCommandFactory& operator=(const VisualizerCommandFactory&) = delete;
	~VisualizerCommandFactory() = default;

	static VisualizerCommandFactory& Instance()
	{
		if (!visualizerCommandFactoryInstance)
			visualizerCommandFactoryInstance = new VisualizerCommandFactory;

		return *visualizerCommandFactoryInstance;
	}

	static void Initialize();
	static void Terminate();

	VisualizerBSphereCommandObjectPool* bSphereCmdPool;
	VisualizerAABBCommandObjectPool* aabbCmdPool;
	VisualizerOBBCommandObjectPool* obbCmdPool;
public:
	static VisualizerBSphereCommand* createBSphereCommand(const CollisionVolumeBSphere& bSph, const Vect& col);
	static void recycleBSphereCommand(VisualizerBSphereCommand* cmd);
	static VisualizerAABBCommand* createAABBCommand(const CollisionVolumeAABB& aabb, const Vect& col);
	static void recycleAABBCommand(VisualizerAABBCommand* cmd);
	static VisualizerOBBCommand* createOBBCommand(const CollisionVolumeOBB& obb, const Vect& col, const Matrix& world);
	static void recycleOBBCommand(VisualizerOBBCommand* cmd);
};

#endif VISUALIZER_COMMAND_FACTORY