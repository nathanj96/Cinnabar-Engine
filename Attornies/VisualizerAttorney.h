#ifndef VISUALIZER_ATTORNEY
#define VISUALIZER_ATTORNEY

#include "Visualizer.h"

class CinnabarEngine;
class VisualizerBSphereCommand;
class VisualizerAABBCommand;
class VisualizerOBBCommand;

class VisualizerAttorney
{
public:
	class GameLoop
	{
		friend class CinnabarEngine;
	private:
		static void Initialize()
		{
			Visualizer::Initialize();
		}
		static void Terminate()
		{
			Visualizer::Terminate();
		}
	};
	class toBSphereCommand
	{
		friend class VisualizerBSphereCommand;
	private:
		static void RenderBSphere(Matrix& S, const Vect& col)
		{
			Visualizer::privRenderBSphere(S, col);
		}
	};
	class toAABBCommand
	{
		friend class VisualizerAABBCommand;
	private:
		static void RenderAABB(Matrix& S, const Vect& col)
		{
			Visualizer::privRenderAABB(S, col);
		}
	};
	class toOBBCommand
	{
		friend class VisualizerOBBCommand;
	private:
		static void RenderOBB(Matrix& S, const Vect& col)
		{
			Visualizer::privRenderOBB(S, col);
		}
	};
};

#endif VISUALIZER_ATTORNEY