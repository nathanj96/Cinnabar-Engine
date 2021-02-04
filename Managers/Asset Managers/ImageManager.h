//Manages images used for sprites

#ifndef IMAGE_MANAGER
#define IMAGE_MANAGER

#include <unordered_map>

#include <string>
using namespace std;

class Image;
class Texture;
struct Rect;
class ImageManagerAttorney;

class ImageManager
{
	friend class ImageManagerAttorney;
private:
	using MapKey = std::string;
	using ImageMap = std::unordered_map<MapKey, Image*>;
	using KeyImagePair = std::pair<MapKey, Image*>;

	std::string defaultPath;
	ImageMap imgMap;

	//Singleton setup
	static ImageManager* imageManagerInstance;

	ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{
		if (!imageManagerInstance)
			imageManagerInstance = new ImageManager;

		return *imageManagerInstance;
	}

	/**********************************************************************************************//**
	 * \fn	static void ImageManager::Terminate();
	 * \ingroup IMAGEMANAGER
	 * \brief	Called when the game ends. Unloads all images. User should not have access to or modify.
	 **************************************************************************************************/

	static void Terminate();
	//On game exit, unload all models
	static void unloadImages();
public:

	/**********************************************************************************************//**
	 * \fn	static Image* ImageManager::getImage(MapKey imgKey);
	 * \ingroup IMAGEMANAGER
	 * \brief	Used to retrieve a given Image.
	 *
	 * \param 	imgKey	The key associated with the Image when it was loaded.
	 *
	 * \returns	The Image with the key imgKey. Throws an error if the key is not found.
	 **************************************************************************************************/

	static Image* getImage(MapKey imgKey);

	/**********************************************************************************************//**
	 * \fn	static void ImageManager::loadImage(MapKey imgKey, Texture* tex);
	 * \ingroup IMAGEMANAGER
	 * \brief	Loads an Image resource using a given Texture. The entire Texture is used for the Image.
	 * 			The image is associated with the key imgKey for future retrieval.
	 *
	 * \param 	imgKey	The image key. The function will throw an error if the provided key is
	 * 					already in use.
	 * \param	tex   	The texture to use. This should be accessed using the function
	 * 					TextureManager::getTexture().
	 **************************************************************************************************/

	static void loadImage(MapKey imgKey, Texture* tex);

	/**********************************************************************************************//**
	 * \fn	static void ImageManager::loadImage(MapKey imgKey, Texture* tex, Rect* r);
	 * \ingroup IMAGEMANAGER
	 * \brief	Loads an Image resource using a given Texture. The portion of the Texture enclosed in the Rect r
	 * 			is used for the Image. The image is associated with the key imgKey for future retrieval.
	 *
	 * \author	Nathan
	 * \date	3/14/2020
	 *
	 * \param 	imgKey	The image key. The function will throw an error if the provided key is
	 * 					already in use.
	 * \param	tex   	The texture to use.
	 * \param	r		The dimensions of the rectangle that will be used to retrieve a subsection of the Texture.
	 * 					Comprised of 4 floats in the format
	 * 					(rectangle top left X, rectangle top left Y, rectangle width, rectangle height).
	 * 					Use as follows:
	 *					\code
	 *						{
	 *							loadImage(key, texture, new Rect(168.0f, 168.0f, 32.0f, 48.0f);
	 *						}
	 *					\endcode
	 **************************************************************************************************/

	static void loadImage(MapKey imgKey, Texture* tex, Rect* r);
};

#endif IMAGE_MANAGER