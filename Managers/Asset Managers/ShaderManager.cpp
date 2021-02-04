#include "ShaderManager.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::shaderManagerInstance = nullptr;

ShaderManager::ShaderManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Shaders/";
}

void ShaderManager::loadShader(MapKey shaderKey, std::string shaderFilename)
{
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	ShaderMap::iterator it = Instance().shaderMap.find(shaderKey);
	if (it != Instance().shaderMap.end())
	{
		throw std::runtime_error("Shader " + shaderKey + " already loaded!");
	}
	else
	{
		std::string insertPath = Instance().defaultPath + shaderFilename;
		//ShaderObject constructor specifically calls for a C-string
		ShaderObject* newShader = new ShaderObject(insertPath.c_str());
		Instance().shaderMap.insert(KeyShaderPair(shaderKey, newShader));
	}
}

ShaderObject* ShaderManager::getShader(MapKey shaderKey)
{
	//Make sure the shader you're looking for is actually present...
	ShaderMap::iterator it = Instance().shaderMap.find(shaderKey);
	if (it == Instance().shaderMap.end())
	{
		throw std::runtime_error("Shader not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

//need to delete the instance pointer on game end too
void ShaderManager::Terminate()
{
	unloadShaders();
	delete shaderManagerInstance;
	shaderManagerInstance = nullptr;
}

void ShaderManager::unloadShaders()
{
	//delete shader objects from the heap
	ShaderMap::iterator it;
	for (it = Instance().shaderMap.begin(); it != Instance().shaderMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}