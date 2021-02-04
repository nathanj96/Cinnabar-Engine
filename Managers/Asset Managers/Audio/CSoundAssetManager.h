//This manager is specifically for the loading/unloading of sound files for CSound objects

#ifndef C_SOUND_ASSET_MANAGER
#define C_SOUND_ASSET_MANAGER

//forward declarations
class CSound;
class CSoundAssetManagerAttorney;

#include <string>
//Map class type that will contain the models - Using unordered map
//because it allows for quicker direct access of elements
#include <unordered_map>

//for std::string
using namespace std;

class CSoundAssetManager
{
	friend class CSoundAssetManagerAttorney;
private:
	//manager-specific type definitions:
	using MapKey = std::string;
	using SoundMap = std::unordered_map<MapKey, CSound*>;
	using KeySoundPair = std::pair<MapKey, CSound*>;
	//The folder that all sound files should be placed in. Saving this
	//location allows the convenience of not having to type the full path
	//name out repeatedly
	std::string defaultPath;
	//use strings to access specific models
	SoundMap soundMap;

	//Singleton setup
	static CSoundAssetManager* CSoundAssetManagerInstance;

	CSoundAssetManager();
	CSoundAssetManager(const CSoundAssetManager&) = delete;
	CSoundAssetManager& operator=(const CSoundAssetManager&) = delete;
	~CSoundAssetManager() = default;

	static CSoundAssetManager& Instance()
	{
		if (!CSoundAssetManagerInstance)
			CSoundAssetManagerInstance = new CSoundAssetManager;

		return *CSoundAssetManagerInstance;
	}

	static void Terminate();
	//On game exit, unload all sounds
	static void unloadSounds();
public:

	/**********************************************************************************************//**
	 * \fn	static CSound* CSoundAssetManager::getSound(MapKey key);
	 * \ingroup CSOUNDASSETMANAGER
	 * \brief	Gets the CSound associated with the given key.
	 *
	 * \param 	key	The key.
	 *
	 * \returns	The CSound with the key. Throws an error if no such sound is found.
	 **************************************************************************************************/

	static CSound* getSound(MapKey key);

	/**********************************************************************************************//**
	 * \fn	static void CSoundAssetManager::loadSound(MapKey soundKey, std::string soundFilename);
	 * \ingroup CSOUNDASSETMANAGER
	 * \brief	Loads a sound file with name soundFilename and stores it in a CSound object, which is
	 * 			associated with key soundKey. Supported formats are  AIFF, ASF, ASX, DLS, FLAC, 
	 * 			IT, M3U, MIDI, MOD, MP2, MP3, Ogg Vorbis, PLS, S3M, VAG (PS2/PSP format), WAV, 
	 * 			WAX (Windows Media Audio Redirector), WMA, and XM.
	 *
	 * \param 	modelKey	 	The key to use.
	 * \param 	soundFilename	Filename of the sound file.
	 **************************************************************************************************/

	static void loadSound(MapKey soundKey, std::string soundFilename);
};

#endif C_SOUND_ASSET_MANAGER