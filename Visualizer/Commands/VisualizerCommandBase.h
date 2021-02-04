#ifndef VISUALIZER_COMMAND_BASE
#define VISUALIZER_COMMAND_BASE

class VisualizerCommandBase
{
public:
	VisualizerCommandBase() = default;
	VisualizerCommandBase(const VisualizerCommandBase&) = default;
	VisualizerCommandBase& operator=(const VisualizerCommandBase&) = default;
	virtual ~VisualizerCommandBase() = default;

	//what needs to be done to process the command? Override in each derived class
	virtual void Execute() = 0;
};

#endif VISUALIZER_COMMAND_BASE