#ifndef VISUALIZER_AABB_COMMAND_OBJECT_POOL
#define VISUALIZER_AABB_COMMAND_OBJECT_POOL

#include <stack>
#include "CollisionVolumeAABB.h"
#include "Vect.h"

class VisualizerAABBCommand;

class VisualizerAABBCommandObjectPool
{
private:
	std::stack<VisualizerAABBCommand*> recycledAABBCommands;
public:
	VisualizerAABBCommandObjectPool() = default;
	VisualizerAABBCommandObjectPool(const VisualizerAABBCommandObjectPool&) = default;
	VisualizerAABBCommandObjectPool& operator=(const VisualizerAABBCommandObjectPool&) = default;
	~VisualizerAABBCommandObjectPool();

	VisualizerAABBCommand* getAABBCommand(const CollisionVolumeAABB& aabb, const Vect& col);
	void returnAABBCommand(VisualizerAABBCommand* cmd);
};

#endif VISUALIZER_AABB_COMMAND_OBJECT_POOL