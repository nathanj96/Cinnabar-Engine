//A manager for all objects that are 'drawable'. This does not strictly have to be GameObjects; rather, this can apply
//to any object that inherits from the Drawable class, though it will be used to update GameObjects

#ifndef DRAWABLE_MANAGER
#define DRAWABLE_MANAGER

//forward declaration
class Drawable;

#include <list>

class DrawableManager
{
private:
	using DrawableList = std::list<Drawable*>;
	DrawableList drawList;
	DrawableList draw2DList;
public:
	using DrawableListRef = DrawableList::iterator;
	DrawableManager() = default;
	//don't allow more than one of the same DrawableManager at once
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;
	~DrawableManager() = default;

	//public because this function will only be called on private member variables of Scene objects
	void processElements();
	void process2DElements();

	void Register(Drawable* up);
	void Register2D(Drawable* up);
	void Deregister(Drawable* up);
	void Deregister2D(Drawable* up);
};

#endif DRAWABLE_MANAGER