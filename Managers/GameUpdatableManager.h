#ifndef GAME_UPDATABLE_MANAGER
#define GAME_UPDATABLE_MANAGER

class GameUpdatable;

#include <list>

class GameUpdatableManager
{
private:
	using UpdatableList = std::list<GameUpdatable*>;
	UpdatableList updateList;
public:
	GameUpdatableManager() = default;
	GameUpdatableManager(const GameUpdatableManager&) = default;
	GameUpdatableManager& operator=(const GameUpdatableManager&) = default;
	~GameUpdatableManager() = default;

	using UpdatableListRef = UpdatableList::iterator;

	void processElements();

	void Register(GameUpdatable* up);
	void Deregister(GameUpdatable* up);
};

#endif GAME_UPDATABLE_MANAGER