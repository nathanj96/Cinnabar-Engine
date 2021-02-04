#include "CSoundChannel.h"
#include "CSoundChannelGroup.h"
#include "CSound.h"
#include "CSoundDSP.h"
#include "CSoundDSPAttorney.h"
#include "SceneAttorney.h"
#include "CChannelSetVolumeCommand.h"
#include "CChannelIncrementVolumeCommand.h"
#include "CChannelPauseCommand.h"
#include "CChannelSetPanCommand.h"
#include "CChannelSetPitchCommand.h"
#include "CChannelAddDSPCommand.h"
#include "CChannelRemoveDSPCommand.h"
#include "CChannelSetPositionCommand.h"
#include "CChannelFastForwardCommand.h"
#include "CChannelRewindCommand.h"
#include "CChannelSet3DCommand.h"
#include "CChannelSet3DAttributesCommand.h"
#include "CChannelSet3DOcclusionCommand.h"
#include "CChannelSetGroupCommand.h"

CSoundChannel::CSoundChannel()
{
	setPosCommandPtr = new CChannelSetPositionCommand(this);
	fastFwdCommandPtr = new CChannelFastForwardCommand(this);
	rwdCommandPtr = new CChannelRewindCommand(this);
	setGrpCommandPtr = new CChannelSetGroupCommand(this);
}

void CSoundChannel::setVol(float newVol)
{
	FMOD_RESULT result;
	result = chnl->setVolume(newVol);
	assert(result == FMOD_OK);
}

void CSoundChannel::incVol(float incAmt)
{
	float vol = GetVolume();
	setVol(vol + incAmt);
}

float CSoundChannel::GetVolume()
{
	float vol;
	FMOD_RESULT result;
	result = chnl->getVolume(&vol);
	assert(result == FMOD_OK);
	return vol;
}

int CSoundChannel::GetIndex() const
{
	int ind;
	FMOD_RESULT result;
	result = chnl->getIndex(&ind);
	assert(result == FMOD_OK);
	return ind;
}

void CSoundChannel::setFMODChannel(FMOD::Channel* newChnl)
{
	chnl = newChnl;
}

FMOD::Channel* CSoundChannel::getFMODChannel() const
{
	return chnl;
}

void CSoundChannel::addDSP(int index, CSoundDSP* dsp)
{
	FMOD_RESULT result;
	result = chnl->addDSP(index, CSoundDSPAttorney::getFMODDSP(dsp));
	assert(result == FMOD_OK);
	//link wrapper classes
	DSPList::iterator it = DSPs.begin() + index;
	DSPs.insert(it, dsp);
}

void CSoundChannel::removeDSP(CSoundDSP* dsp)
{
	FMOD_RESULT result;
	result = chnl->removeDSP(CSoundDSPAttorney::getFMODDSP(dsp));
	assert(result == FMOD_OK);
	//internal list cleanup
	DSPList::iterator it = std::find(DSPs.begin(), DSPs.end(), dsp);
	DSPs.erase(it);
}

void CSoundChannel::setSound(CSound* newSound)
{
	soundPlaying = newSound;
}

void CSoundChannel::setPause(bool newPaused)
{
	FMOD_RESULT result;
	result = chnl->setPaused(newPaused);
	assert(result == FMOD_OK);
}

bool CSoundChannel::GetPaused()
{
	bool paused;
	FMOD_RESULT result;
	result = chnl->getPaused(&paused);
	assert(result == FMOD_OK);
	return paused;
}

void CSoundChannel::setPan(float newPan)
{
	FMOD_RESULT result;
	result = chnl->setPan(newPan);
	assert(result == FMOD_OK);
}

void CSoundChannel::SetPosition(unsigned int newPos)
{
	setPosCommandPtr->setNewPos(newPos);
	SceneAttorney::toCAudio::submitCSoundCommand(setPosCommandPtr);
}

void CSoundChannel::setPos(unsigned int newPos)
{
	FMOD_RESULT result;
	//FMOD throws an error if you try setting the position to exactly the end of the sound. Setting it to 1
	//millisecond before is effectively the same from the user perspective, so I'm encapsulating that for them
	if (newPos >= soundPlaying->getLength())
	{
		newPos = soundPlaying->getLength() - 1;
	}
	result = chnl->setPosition(newPos, FMOD_TIMEUNIT_MS);
	assert(result == FMOD_OK);
}

unsigned int CSoundChannel::GetPosition() const
{
	unsigned int pos;
	FMOD_RESULT result;
	result = chnl->getPosition(&pos, FMOD_TIMEUNIT_MS);
	assert(result == FMOD_OK);
	return pos;
}

void CSoundChannel::setPitch(float newPitch)
{
	FMOD_RESULT result;
	result = chnl->setPitch(newPitch);
	assert(result == FMOD_OK);
}

float CSoundChannel::GetPitch()
{
	float pitch;
	FMOD_RESULT result;
	result = chnl->getPitch(&pitch);
	assert(result == FMOD_OK);
	return pitch;
}

void CSoundChannel::FastForward(unsigned int amt)
{
	fastFwdCommandPtr->setNewFwdAmt(amt);
	SceneAttorney::toCAudio::submitCSoundCommand(fastFwdCommandPtr);
}

void CSoundChannel::fastFwd(unsigned int amt)
{
	unsigned int pos = GetPosition();
	//setPos already checks to make sure pos isn't past the end of the sound
	setPos(pos + amt);
}

void CSoundChannel::Rewind(unsigned int amt)
{
	rwdCommandPtr->setNewRwdAmt(amt);
	SceneAttorney::toCAudio::submitCSoundCommand(rwdCommandPtr);
}

void CSoundChannel::rwd(unsigned int amt)
{
	//pos needs to be SIGNED here. If subtracting amt from pos would result in it being negative, and pos
	//were unsigned, it would overflow
	int pos = GetPosition();
	pos -= amt;
	//make sure pos isn't before the start of the sound
	if (pos < 0)
	{
		pos = 0;
	}
	setPos(pos);
}

void CSoundChannel::set3D(bool _3D)
{
	FMOD_RESULT result;
	//retrieve current FMOD mode first
	FMOD_MODE mode;
	result = chnl->getMode(&mode);
	assert(result == FMOD_OK);
	if (_3D)
	{
		//unset the 2D flag
		mode = mode ^ FMOD_2D;
		//prevent double setting. This checks the bit in mode corresponding to FMOD_2D and makes sure it is unset. If it is not,
		//that means this function was called on a sound that already had FMOD_3D set instead.
		if (((mode >> 3) & 1) != 0)
		{
			throw std::runtime_error("Channel is already 3D!");
		}
		//then set 3D flag
		mode = mode | FMOD_3D;
		//making sure I'm setting the 3D bit(0x00000010) properly...
		assert(((mode >> 4) & 1) == 1);
		result = chnl->setMode(mode);
		assert(result == FMOD_OK);
	}
	else
	{
		//unset the 3D flag
		mode = mode ^ FMOD_3D;
		//prevent double setting. This checks the bit in mode corresponding to FMOD_3D and makes sure it is unset. If it is not,
		//that means this function was called on a sound that already had FMOD_2D set instead.
		if(((mode >> 4) & 1) != 0)
		{
			throw std::runtime_error("Channel is already 2D!");
		}
		//then set 2D flag
		mode = mode | FMOD_2D;
		//making sure I'm setting the 2D bit(0x00000008) properly...
		assert(((mode >> 3) & 1) == 1);
		result = chnl->setMode(mode);
		assert(result == FMOD_OK);
	}
}

void CSoundChannel::set3DAttrs(const Vect& pos, const Vect& vel)
{
	FMOD_RESULT result;

	//conversion to FMOD vectors.....
	FMOD_VECTOR FMODpos;
	FMODpos.x = pos.X();
	FMODpos.y = pos.Y();
	FMODpos.z = pos.Z();
	FMOD_VECTOR FMODvel;
	FMODvel.x = vel.X();
	FMODvel.y = vel.Y();
	FMODvel.z = vel.Z();

	result = chnl->set3DAttributes(&FMODpos, &FMODvel);
	assert(result == FMOD_OK);
}

void CSoundChannel::set3DOcclusion(float directOcclusion, float reverbOcclusion)
{
	FMOD_RESULT result;
	result = chnl->set3DOcclusion(directOcclusion, reverbOcclusion);
	assert(result == FMOD_OK);
}

void CSoundChannel::SetChannelGroup(CSoundChannelGroup* newGrp)
{
	setGrpCommandPtr->setNewChannelGroup(newGrp);
	SceneAttorney::toCAudio::submitCSoundCommand(setGrpCommandPtr);
}

void CSoundChannel::setChnlGrp(CSoundChannelGroup* newGrp)
{
	FMOD_RESULT result;
	FMOD::ChannelGroup* FMODgrp = newGrp->getFMODGrp();
	result = chnl->setChannelGroup(FMODgrp);
	assert(result == FMOD_OK);
}

CSoundChannel::~CSoundChannel()
{
	delete setPosCommandPtr;
	setPosCommandPtr = nullptr;
	delete fastFwdCommandPtr;
	fastFwdCommandPtr = nullptr;
	delete rwdCommandPtr;
	rwdCommandPtr = nullptr;
	delete setGrpCommandPtr;
	setGrpCommandPtr = nullptr;
}