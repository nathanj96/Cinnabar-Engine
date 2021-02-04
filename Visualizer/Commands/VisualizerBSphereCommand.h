#ifndef VISUALIZER_BSPHERE_COMMAND
#define VISUALIZER_BSPHERE_COMMAND

#include "VisualizerCommandBase.h"
#include "CollisionVolumeBSphere.h"
#include "Vect.h"

class VisualizerBSphereCommand : public VisualizerCommandBase
{
private:
	CollisionVolumeBSphere BSph;
	Vect col;
public:
	VisualizerBSphereCommand() = delete;
	VisualizerBSphereCommand(const VisualizerBSphereCommand&) = delete;
	VisualizerBSphereCommand& operator=(const VisualizerBSphereCommand&) = delete;
	~VisualizerBSphereCommand() = default;

	VisualizerBSphereCommand(const CollisionVolumeBSphere& sph, const Vect& color);

	virtual void Execute() override;

	//enable resetting of data members so commands can be reused
	void SetBSphere(const CollisionVolumeBSphere& newSphere);
	void SetColor(const Vect& newColor);
};

#endif VISUALIZER_BSPHERE_COMMAND