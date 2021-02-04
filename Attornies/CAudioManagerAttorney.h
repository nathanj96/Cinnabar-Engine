#ifndef C_AUDIO_MANAGER_ATTORNEY
#define C_AUDIO_MANAGER_ATTORNEY

class CSound;

#include "CAudioManager.h"

class CAudioManagerAttorney
{
public:
	class gameLoop
	{
		friend class CinnabarEngine;
	private:
		static void Update()
		{
			CAudioManager::Update();
		}
		static void Initialize()
		{
			CAudioManager::Initialize();
		}
		static void Terminate()
		{
			CAudioManager::Terminate();
		}
	};
	class toCSound
	{
		friend class CSound;
	private:
		static CAudioManager& Instance()
		{
			return CAudioManager::Instance();
		}
		//static void playSound(FMOD::Sound* sound, bool startPaused)
		//{
		//	CAudioManager::playSound(sound, startPaused);
		//}
		//static void playSoundAndSaveChannel(FMOD::Sound* sound, bool startPaused, CSoundChannel** newChannel)
		//{
		//	CAudioManager::playSoundAndSaveChannel(sound, startPaused, newChannel);
		//}
		//static FMOD_RESULT createSound(const char* fileName, FMOD::Sound** sound)
		//{
		//	return CAudioManager::createSound(fileName, sound);
		//}
	};
};

#endif C_AUDIO_MANAGER_ATTORNEY