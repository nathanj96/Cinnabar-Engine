#ifndef C_SOUND_ATTORNEY
#define C_SOUND_ATTORNEY

class CSoundPlayCommand;

#include "CSound.h"

class CSoundAttorney
{
	friend class CSoundPlayCommand;
private:
	static void playSound(CSound* snd, bool startPaused, CSoundChannel* newChannel)
	{
		snd->playSound(startPaused, newChannel);
	}
};

#endif C_SOUND_ATTORNEY