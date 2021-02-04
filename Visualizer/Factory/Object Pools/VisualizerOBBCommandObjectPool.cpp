#include "VisualizerOBBCommandObjectPool.h"
#include "VisualizerOBBCommand.h"

VisualizerOBBCommandObjectPool::~VisualizerOBBCommandObjectPool()
{
	while (!recycledOBBCommands.empty())
	{
		delete recycledOBBCommands.top();
		recycledOBBCommands.pop();
	}
}

VisualizerOBBCommand* VisualizerOBBCommandObjectPool::getOBBCommand(const CollisionVolumeOBB& vol, const Vect& col, const Matrix& world)
{
	VisualizerOBBCommand* cmd;
	if (recycledOBBCommands.empty())
	{
		cmd = new VisualizerOBBCommand(vol, col, world);
	}
	else
	{
		cmd = recycledOBBCommands.top();
		recycledOBBCommands.pop();
		cmd->SetOBB(vol);
		cmd->SetColor(col);
		cmd->SetWorld(world);
	}
	return cmd;
}

void VisualizerOBBCommandObjectPool::returnOBBCommand(VisualizerOBBCommand* cmd)
{
	recycledOBBCommands.push(cmd);
}