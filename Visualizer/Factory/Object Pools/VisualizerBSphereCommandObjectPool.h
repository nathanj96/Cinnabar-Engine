#ifndef VISUALIZER_BSPHERE_COMMAND_OBJECT_POOL
#define VISUALIZER_BSPHERE_COMMAND_OBJECT_POOL

#include <stack>
#include "CollisionVolumeBSphere.h"
#include "Vect.h"

class VisualizerBSphereCommand;

class VisualizerBSphereCommandObjectPool
{
private:
	std::stack<VisualizerBSphereCommand*> recycledBSphereCommands;
public:
	VisualizerBSphereCommandObjectPool() = default;
	VisualizerBSphereCommandObjectPool(const VisualizerBSphereCommandObjectPool&) = default;
	VisualizerBSphereCommandObjectPool& operator=(const VisualizerBSphereCommandObjectPool&) = default;
	~VisualizerBSphereCommandObjectPool();

	VisualizerBSphereCommand* getBSphereCommand(const CollisionVolumeBSphere& bSph, const Vect& col);
	void returnBSphereCommand(VisualizerBSphereCommand* cmd);
};

#endif VISUALIZER_BSPHERE_COMMAND_OBJECT_POOL