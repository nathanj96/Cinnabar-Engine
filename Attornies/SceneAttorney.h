#ifndef SCENE_ATTORNEY
#define SCENE_ATTORNEY

#include "Scene.h"
#include "SceneManager.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Alarmable.h"
#include "AlarmableManager.h"
#include "Inputable.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"

class Collidable;
class GameObject;
class Visualizer;
class CSound;

#include "RegistrationCommandBase.h"
#include "VisualizerCommandBase.h"

//note: the SubmitCommand() wrapper is redefined for each class for readability and because I can't templatize it since not every
//class has registration commands

class SceneAttorney
{
public:
	class toUpdatable
	{
		friend class Updatable;
	private:
		static void submitUpdateCommand(RegistrationCommandBase* com)
		{
			SceneManager::getCurrentScene()->SubmitCommand(com);
		}
		static void registerUpdate(Updatable* up)
		{
			SceneManager::getCurrentScene()->RegisterUpdate(up);
		}
		static void deregisterUpdate(Updatable* up)
		{
			SceneManager::getCurrentScene()->DeregisterUpdate(up);
		}
	};
	class toDrawable
	{
		friend class Drawable;
	private:
		static void submitDrawCommand(RegistrationCommandBase* com)
		{
			SceneManager::getCurrentScene()->SubmitCommand(com);
		}
		static void registerDraw(Drawable* draw)
		{
			SceneManager::getCurrentScene()->RegisterDraw(draw);
		}
		static void deregisterDraw(Drawable* draw)
		{
			SceneManager::getCurrentScene()->DeregisterDraw(draw);
		}
		static void registerDraw2D(Drawable* draw)
		{
			SceneManager::getCurrentScene()->RegisterDraw2D(draw);
		}
		static void deregisterDraw2D(Drawable* draw)
		{
			SceneManager::getCurrentScene()->DeregisterDraw2D(draw);
		}
	};
	class toAlarmable
	{
		friend class Alarmable;
	private:
		static void submitAlarmCommand(RegistrationCommandBase* com)
		{
			SceneManager::getCurrentScene()->SubmitCommand(com);
		}
		static void registerAlarm(float t, Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
		{
			SceneManager::getCurrentScene()->RegisterAlarm(t, alarm, alarmNumber);
		}
		static void deregisterAlarm(Alarmable* alarm, AlarmableManager::AlarmNum alarmNumber)
		{
			SceneManager::getCurrentScene()->DeregisterAlarm(alarm, alarmNumber);
		}
	};
	class toInputable
	{
		friend class Inputable;
	private:
		static void submitInputCommand(RegistrationCommandBase* com)
		{
			SceneManager::getCurrentScene()->SubmitCommand(com);
		}
		static void registerKeyPress(Inputable* in, AZUL_KEY k)
		{
			SceneManager::getCurrentScene()->RegisterKeyPress(in, k);
		}
		static void registerKeyRelease(Inputable* in, AZUL_KEY k)
		{
			SceneManager::getCurrentScene()->RegisterKeyRelease(in, k);
		}
		static void deregisterKeyPress(Inputable* in, AZUL_KEY k)
		{
			SceneManager::getCurrentScene()->DeregisterKeyPress(in, k);
		}
		static void deregisterKeyRelease(Inputable* in, AZUL_KEY k)
		{
			SceneManager::getCurrentScene()->DeregisterKeyRelease(in, k);
		}
	};
	class toGameObject
	{
		friend class GameObject;
	private:
		static void submitEntryExitCommand(RegistrationCommandBase* cmd)
		{
			SceneManager::getCurrentScene()->SubmitCommand(cmd);
		}
	};
	class toCollidable
	{
		friend class Collidable;
	private:
		template<typename C> static CollisionManager::CTypeID GetTypeID()
		{
			return SceneManager::getCurrentScene()->getCollisionMgr()->GetTypeID<C>();
		}
		static void submitCollidableCommand(RegistrationCommandBase* cmd)
		{
			SceneManager::getCurrentScene()->SubmitCommand(cmd);
		}
		static void registerCollidable(CollisionManager::CTypeID id, Collidable* col)
		{
			SceneManager::getCurrentScene()->getCollisionMgr()->GetColGroup(id)->Register(col);
		}
		static void deregisterCollidable(CollisionManager::CTypeID id, Collidable* col)
		{
			SceneManager::getCurrentScene()->getCollisionMgr()->GetColGroup(id)->Deregister(col);
		}
	};
	class toSceneManager
	{
		friend class SceneManager;
	private:
		static void Initialize(Scene* sc)
		{
			sc->Initialize();
		}
		static void SceneEnd(Scene* sc)
		{
			sc->SceneEnd();
		}
		static void Update(Scene* sc)
		{
			sc->Update();
		}
		static void Draw(Scene* sc)
		{
			sc->Draw();
		}
	};
	class toVisualizer
	{
		friend class Visualizer;
	private:
		static void submitVisualizerCommand(VisualizerCommandBase* cmd)
		{
			SceneManager::getCurrentScene()->SubmitCommand(cmd);
		}
	};
	class toCAudio
	{
		friend class CSound;
		friend class CSoundChannelBase;
		friend class CSoundChannel;
	private:
		static void submitCSoundCommand(CAudioCommandBase* cmd)
		{
			SceneManager::getCurrentScene()->SubmitCommand(cmd);
		}
	};
};
#endif SCENE_ATTORNEY