#include "ImageManager.h"
//all 3 are necessary to construct images
#include "Image.h"
#include "Texture.h"
#include "Rect.h"

ImageManager* ImageManager::imageManagerInstance = nullptr;

ImageManager::ImageManager()
{
	//I can't make this assignment if it's a const string?
	defaultPath = "Images/";
}

void ImageManager::Terminate()
{
	unloadImages();
	delete imageManagerInstance;
	imageManagerInstance = nullptr;
}

void ImageManager::unloadImages()
{
	//delete image objects from the heap
	ImageMap::iterator it;
	for (it = Instance().imgMap.begin(); it != Instance().imgMap.end(); it++)
	{
		delete (*it).second;
		(*it).second = nullptr;
	}
}

Image* ImageManager::getImage(MapKey imgKey)
{
	//Make sure the image you're looking for is actually present...
	ImageMap::iterator it = Instance().imgMap.find(imgKey);
	if (it == Instance().imgMap.end())
	{
		throw std::runtime_error("Image " + imgKey + " not found!");
	}
	//(*iterator).second returns the value of an iterator
	return (*it).second;
}

void ImageManager::loadImage(MapKey imgKey, Texture* tex)
{
	//Load an image using an entire texture
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	ImageMap::iterator it = Instance().imgMap.find(imgKey);
	if (it != Instance().imgMap.end())
	{
		throw std::runtime_error("Image " + imgKey + " already loaded!");
	}
	else
	{
		Image* newImage = new Image(tex, new Rect(0.0f, 0.0f, (float)tex->getWidth(), (float)tex->getHeight()));
		Instance().imgMap.insert(KeyImagePair(imgKey, newImage));
	}
}

void ImageManager::loadImage(MapKey imgKey, Texture* tex, Rect* r)
{
	//Load an image using only part of a texture via a passed-in Rect
	//check that you aren't trying to load a resource that has already been loaded (unordered maps
	//already have this functionality but just to show that I understand it)
	ImageMap::iterator it = Instance().imgMap.find(imgKey);
	if (it != Instance().imgMap.end())
	{
		throw std::runtime_error("Image " + imgKey + " already loaded!");
	}
	else
	{
		Image* newImage = new Image(tex, r);
		Instance().imgMap.insert(KeyImagePair(imgKey, newImage));
	}
}