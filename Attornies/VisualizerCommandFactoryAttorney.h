#ifndef VISUALIZER_COMMAND_FACTORY_ATTORNEY
#define VISUALIZER_COMMAND_FACTORY_ATTORNEY

#include "VisualizerCommandFactory.h"

class VisualizerCommandFactoryAttorney
{
	friend class CinnabarEngine;
private:
	static void Initialize()
	{
		VisualizerCommandFactory::Initialize();
	}
	static void Terminate()
	{
		VisualizerCommandFactory::Terminate();
	}
};

#endif VISUALIZER_COMMAND_FACTORY_ATTORNEY