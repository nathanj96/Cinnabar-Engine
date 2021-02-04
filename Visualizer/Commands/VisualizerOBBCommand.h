#ifndef VISUALIZER_OBB_COMMAND
#define VISUALIZER_OBB_COMMAND

#include "VisualizerCommandBase.h"
#include "CollisionVolumeOBB.h"
#include "Vect.h"
#include "Matrix.h"

class VisualizerOBBCommand : public VisualizerCommandBase
{
private:
	CollisionVolumeOBB obb;
	Vect col;
	Matrix world;
public:
	VisualizerOBBCommand() = delete;
	VisualizerOBBCommand(const VisualizerOBBCommand&) = default;
	VisualizerOBBCommand& operator=(const VisualizerOBBCommand&) = default;
	~VisualizerOBBCommand() = default;

	VisualizerOBBCommand(const CollisionVolumeOBB& vol, const Vect& color, const Matrix& worldMat);

	virtual void Execute() override;

	//enable resetting of data members so commands can be reused
	void SetOBB(const CollisionVolumeOBB& newOBB);
	void SetColor(const Vect& newColor);
	void SetWorld(const Matrix& newMatrix);
};

#endif VISUALIZER_OBB_COMMAND