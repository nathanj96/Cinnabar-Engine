//Manager for controlling the loading and retrieval of shaders

#ifndef SHADER_MANAGER
#define SHADER_MANAGER

//forward declaration
class ShaderObject;
class ShaderObjectAttorney;

#include <string>
//Map class type that will contain the shaders - Using unordered map
//because it allows for quicker direct access of elements
#include <unordered_map>

//for std::string
using namespace std;

//Manager for controlling the loading and retrieval of shaders

class ShaderManager
{
	friend class ShaderManagerAttorney;
private:
	//manager::specific type definitions:
	using MapKey = std::string;
	using ShaderMap = std::unordered_map<MapKey, ShaderObject*>;
	using KeyShaderPair = std::pair<MapKey, ShaderObject*>;

	//The folder that all shader assets should be placed in. Saving this
	//location allows the convenience of not having to type the full path
	//name out repeatedly
	std::string defaultPath;
	//use strings to access specific shaders
	ShaderMap shaderMap;

	//Singleton setup
	static ShaderManager* shaderManagerInstance;

	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance()
	{
		if (!shaderManagerInstance)
			shaderManagerInstance = new ShaderManager;

		return *shaderManagerInstance;
	}

	//On game exit, unload all shaders
	static void unloadShaders();

	/**********************************************************************************************//**
	 * \fn	static void ShaderManager::Terminate();
	 * \ingroup SHADERMANAGER
	 * \brief	Called when the game ends. Unloads all shaders. User should not have access to or modify.
	 **************************************************************************************************/

	static void Terminate();
public:
	/**********************************************************************************************//**
	 * \fn	static ShaderObject* ShaderManager::getShader(MapKey shaderKey);
	 * \ingroup SHADERMANAGER
	 * \brief	Used to retrieve a given ShaderObject.
	 *
	 * \param 	shaderKey	The key associated with the ShaderObject when it was loaded.
	 *
	 * \returns	The ShaderObject with the given key. Throws an error if the key is not found.
	 **************************************************************************************************/
	static ShaderObject* getShader(MapKey shaderKey);

	/**********************************************************************************************//**
	 * \fn	static void ShaderManager::loadShader(MapKey shaderKey, std::string shaderFilename);
	 * \ingroup SHADERMANAGER
	 * \brief	Loads a given shader file. The shader is associated with the key shaderKey for future retrieval.
	 *
	 * \param 	shaderKey	 	The shader key.
	 * \param 	modelFilename	Filename of the shader file. Specify <b>only</b> the name of the file, as such:
	 *							\code
	 *								 {
	 *								 ShaderManager::loadShader("newShader", "TextureShader");
	 *								 }
	 *							\endcode
	 **************************************************************************************************/
	static void loadShader(MapKey shaderKey, std::string shaderFilename);
};

#endif SHADER_MANAGER