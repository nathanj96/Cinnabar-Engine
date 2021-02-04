#include "VisualizerBSphereCommandObjectPool.h"
#include "VisualizerBSphereCommand.h"

VisualizerBSphereCommandObjectPool::~VisualizerBSphereCommandObjectPool()
{
	while (!recycledBSphereCommands.empty())
	{
		delete recycledBSphereCommands.top();
		recycledBSphereCommands.pop();
	}
}

VisualizerBSphereCommand* VisualizerBSphereCommandObjectPool::getBSphereCommand(const CollisionVolumeBSphere& bSph, const Vect& col)
{
	VisualizerBSphereCommand* cmd;
	if (recycledBSphereCommands.empty())
	{
		cmd = new VisualizerBSphereCommand(bSph, col);
	}
	else
	{
		cmd = recycledBSphereCommands.top();
		recycledBSphereCommands.pop();
		cmd->SetBSphere(bSph);
		cmd->SetColor(col);
	}
	return cmd;
}

void VisualizerBSphereCommandObjectPool::returnBSphereCommand(VisualizerBSphereCommand* cmd)
{
	recycledBSphereCommands.push(cmd);
}