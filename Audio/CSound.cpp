#include "CSound.h"
#include "CAudioManager.h"
#include "CSoundChannel.h"
#include "CAudioCommandBase.h"
#include "CSoundPlayCommand.h"
#include "SceneAttorney.h"
#include <cmath>

CSound::CSound(const char* fileName)
{
	FMOD_RESULT result;
	result = CAudioManager::CreateFMODSound(fileName, &snd);
	assert(result == FMOD_OK);
	playSoundCmdPtr = new CSoundPlayCommand(this, false, nullptr);
}

void CSound::Play(bool startPaused, CSoundChannel* newChannel)
{
	playSoundCmdPtr->setStartPaused(startPaused);
	playSoundCmdPtr->setNewChannel(newChannel);
	SceneAttorney::toCAudio::submitCSoundCommand(playSoundCmdPtr);
}

void CSound::playSound(bool startPaused, CSoundChannel* newChannel)
{
	CAudioManager::PlayFMODSound(snd, startPaused, newChannel);
	newChannel->setSound(this);
}

void CSound::SetNumLoops(int numLoops)
{
	FMOD_RESULT result;
	result = snd->setLoopCount(numLoops);
	assert(result == FMOD_OK);
}

int CSound::GetNumLoops() const
{
	int numLoops;
	FMOD_RESULT result;
	result = snd->getLoopCount(&numLoops);
	assert(result == FMOD_OK);
	return numLoops;
}

void CSound::SetLoopStartAndEnd(unsigned int start, unsigned int end)
{
	FMOD_RESULT result;
	//make sure the loop isn't set to start after it ends
	if (start > end)
	{
		throw std::runtime_error("Loop start must be less than or equal to loop end!");
	}
	result = snd->setLoopPoints(start, FMOD_TIMEUNIT_MS, end, FMOD_TIMEUNIT_MS);
	assert(result == FMOD_OK);
};

unsigned int CSound::getLength() const
{
	unsigned int len;
	FMOD_RESULT result;
	result = snd->getLength(&len, FMOD_TIMEUNIT_MS);
	assert(result == FMOD_OK);
	return len;
}

void CSound::Set3D(bool _3D)
{
	FMOD_RESULT result;
	//retrieve current FMOD mode first
	FMOD_MODE mode;
	result = snd->getMode(&mode);
	assert(result == FMOD_OK);
	if (_3D)
	{
		//unset the 2D flag
		mode = mode ^ FMOD_2D;
		//making sure I'm unsetting the 2D bit(0x00000008) properly...
		assert(((mode >> 3) & 1) == 0);
		//then set 3D flag
		mode = mode | FMOD_3D;
		//making sure I'm setting the 3D bit(0x00000010) properly...
		assert(((mode >> 4) & 1) == 1);
		result = snd->setMode(mode);
		assert(result == FMOD_OK);
	}
	else
	{
		//set the 2D flag
		mode = mode | FMOD_2D;
		//making sure I'm setting the 2D bit(0x00000008) properly...
		assert(((mode >> 3) & 1) == 1);
		//then unset 3D flag
		mode = mode ^ FMOD_3D;
		//making sure I'm unsetting the 3D bit(0x00000010) properly...
		assert(((mode >> 4) & 1) == 0);
		result = snd->setMode(mode);
		assert(result == FMOD_OK);
	}
}

void CSound::Set3DMinAndMaxAudibleDistance(float minDist, float maxDist)
{
	FMOD_RESULT result;
	result = snd->set3DMinMaxDistance(minDist, maxDist);
	assert(result == FMOD_OK);
}

CSound::~CSound()
{
	FMOD_RESULT result;
	result = snd->release();
	assert(result == FMOD_OK);
	delete playSoundCmdPtr;
	playSoundCmdPtr = nullptr;
}