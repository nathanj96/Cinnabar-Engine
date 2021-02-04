#ifndef SHADER_MANAGER_ATTORNEY
#define SHADER_MANAGER_ATTORNEY

#include "ShaderManager.h"

class CinnabarEngine;

class ShaderManagerAttorney
{
	//giving it access to Terminate()
	friend class CinnabarEngine;
private:
	static void Terminate()
	{
		ShaderManager::Terminate();
	}
};

#endif SHADER_MANAGER_ATTORNEY