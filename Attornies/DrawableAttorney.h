#ifndef DRAWABLE_ATTORNEY
#define DRAWABLE_ATTORNEY

class DrawableManager;
class RegisterDrawCommand;
class DeregisterDrawCommand;

#include "Drawable.h"

class DrawableAttorney
{
public:
	class GameLoop
	{
		//giving access to Draw()
		friend class DrawableManager;
	private:
		static void Draw(Drawable* draw)
		{
			draw->Draw();
		}
		static void Draw2D(Drawable* draw)
		{
			draw->Draw2D();
		}
	};
	class Registration
	{
		friend class RegisterDrawCommand;
		friend class DeregisterDrawCommand;
		friend class DrawableManager;
	private:
		static void RegisterDrawable(Drawable* draw)
		{
			draw->RegisterDrawable();
		}
		static void DeregisterDrawable(Drawable* draw)
		{
			draw->DeregisterDrawable();
		}
		static void RegisterDrawable2D(Drawable* draw)
		{
			draw->RegisterDrawable2D();
		}
		static void DeregisterDrawable2D(Drawable* draw)
		{
			draw->DeregisterDrawable2D();
		}
		static void setDrawObjRef(Drawable* draw, DrawableManager::DrawableListRef ref)
		{
			draw->setDrawObjRef(ref);
		}
	};
	class Registration2D
	{
		friend class RegisterDraw2DCommand;
		friend class DeregisterDraw2DCommand;
	private:
		static void RegisterDrawable2D(Drawable* draw)
		{
			draw->RegisterDrawable2D();
		}
		static void DeregisterDrawable2D(Drawable* draw)
		{
			draw->DeregisterDrawable2D();
		}
	};
};

#endif DRAWABLE_ATTORNEY