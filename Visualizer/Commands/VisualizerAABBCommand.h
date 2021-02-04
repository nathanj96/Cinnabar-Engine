#ifndef VISUALIZER_AABB_COMMAND
#define VISUALIZER_AABB_COMMAND

#include "VisualizerCommandBase.h"
#include "CollisionVolumeAABB.h"
#include "Vect.h"

class VisualizerAABBCommand : public VisualizerCommandBase
{
private:
	CollisionVolumeAABB aabb;
	Vect col;
public:
	VisualizerAABBCommand() = delete;
	VisualizerAABBCommand(const VisualizerAABBCommand&) = delete;
	VisualizerAABBCommand& operator=(const VisualizerAABBCommand&) = delete;
	~VisualizerAABBCommand() = default;

	VisualizerAABBCommand(const CollisionVolumeAABB& vol, const Vect& color);

	virtual void Execute() override;

	//enable resetting of data members so commands can be reused
	void SetAABB(const CollisionVolumeAABB& newAABB);
	void SetColor(const Vect& newColor);
};

#endif VISUALIZER_AABB_COMMAND