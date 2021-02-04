#include "CSoundPlayCommand.h"
#include "CSoundAttorney.h"

CSoundPlayCommand::CSoundPlayCommand(CSound* sound, bool pause, CSoundChannel* channel) : snd(sound), startPaused(pause), newChannel(channel)
{
};

void CSoundPlayCommand::Execute()
{
	CSoundAttorney::playSound(snd, startPaused, newChannel);
}

void CSoundPlayCommand::setStartPaused(bool newVal)
{
	startPaused = newVal;
}

void CSoundPlayCommand::setNewChannel(CSoundChannel* val)
{
	newChannel = val;
}