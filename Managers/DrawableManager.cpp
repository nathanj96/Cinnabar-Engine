#include "DrawableManager.h"
#include "DrawableAttorney.h"
#include "DebugOut.h"

void DrawableManager::Register(Drawable* draw)
{
	//insert an element into the list, then save its iterator inside the element for constant ti0me removal later
	DrawableAttorney::Registration::setDrawObjRef(draw, drawList.insert(drawList.end(), draw));
	//DebugMsg::out("Drawable registered\n");
}

void DrawableManager::Register2D(Drawable* draw)
{
	//insert an element into the list, then save its iterator inside the element for constant time removal later
	DrawableAttorney::Registration::setDrawObjRef(draw, draw2DList.insert(draw2DList.end(), draw));
	//DebugMsg::out("Drawable registered\n");
}

void DrawableManager::Deregister(Drawable* draw)
{
	drawList.erase(draw->getDrawObjRef());
	//DebugMsg::out("Drawable deregistered\n");
}

void DrawableManager::Deregister2D(Drawable* draw)
{
	draw2DList.erase(draw->getDrawObjRef());
	//DebugMsg::out("Drawable deregistered\n");
}

void DrawableManager::processElements()
{
	//render 3d elements first
	//not using the local space name for clarity
	DrawableList::iterator it;
	for (it = drawList.begin(); it != drawList.end(); it++)
	{
		DrawableAttorney::GameLoop::Draw(*it);
	}
	//go through 2D elements after so they appear on top
	process2DElements();
}

void DrawableManager::process2DElements()
{
	//not using the local space name for clarity
	DrawableList::iterator it;
	for (it = draw2DList.begin(); it != draw2DList.end(); it++)
	{
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
}