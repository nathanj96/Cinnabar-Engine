#ifndef VISUALIZER_OBB_COMMAND_OBJECT_POOL
#define VISUALIZER_OBB_COMMAND_OBJECT_POOL

#include <stack>
#include "CollisionVolumeOBB.h"
#include "Vect.h"
#include "Matrix.h"

class VisualizerOBBCommand;

class VisualizerOBBCommandObjectPool
{
private:
	std::stack<VisualizerOBBCommand*> recycledOBBCommands;
public:
	VisualizerOBBCommandObjectPool() = default;
	VisualizerOBBCommandObjectPool(const VisualizerOBBCommandObjectPool&) = default;
	VisualizerOBBCommandObjectPool& operator=(const VisualizerOBBCommandObjectPool&) = default;
	~VisualizerOBBCommandObjectPool();

	VisualizerOBBCommand* getOBBCommand(const CollisionVolumeOBB& vol, const Vect& col, const Matrix& world);
	void returnOBBCommand(VisualizerOBBCommand* cmd);
};

#endif VISUALIZER_OBB_COMMAND_OBJECT_POOL
