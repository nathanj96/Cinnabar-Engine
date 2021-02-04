#include "VisualizerAABBCommandObjectPool.h"
#include "VisualizerAABBCommand.h"

VisualizerAABBCommandObjectPool::~VisualizerAABBCommandObjectPool()
{
	while (!recycledAABBCommands.empty())
	{
		delete recycledAABBCommands.top();
		recycledAABBCommands.pop();
	}
}

VisualizerAABBCommand* VisualizerAABBCommandObjectPool::getAABBCommand(const CollisionVolumeAABB& aabb, const Vect& col)
{
	VisualizerAABBCommand* cmd;
	if (recycledAABBCommands.empty())
	{
		cmd = new VisualizerAABBCommand(aabb, col);
	}
	else
	{
		cmd = recycledAABBCommands.top();
		recycledAABBCommands.pop();
		cmd->SetAABB(aabb);
		cmd->SetColor(col);
	}
	return cmd;
}

void VisualizerAABBCommandObjectPool::returnAABBCommand(VisualizerAABBCommand* cmd)
{
	recycledAABBCommands.push(cmd);
}