#include "CSoundChannelGroup.h"
#include "CSoundDSPAttorney.h"
#include "CAudioManager.h"

CSoundChannelGroup::CSoundChannelGroup()
{
	FMOD_RESULT result;
	result = CAudioManager::CreateFMODChannelGroup(&chnlGrp);
	assert(result == FMOD_OK);
	//initialize all sounds as 3D, so force the channel group to be 3D at the beginning too to be able to play them
	chnlGrp->setMode(FMOD_3D);
	chnlGrp->setMode(FMOD_LOOP_NORMAL);
}

void CSoundChannelGroup::setVol(float newVol)
{
	FMOD_RESULT result;
	result = chnlGrp->setVolume(newVol);
	assert(result == FMOD_OK);
}

float CSoundChannelGroup::GetVolume()
{
	float vol;
	FMOD_RESULT result;
	result = chnlGrp->getVolume(&vol);
	assert(result == FMOD_OK);
	return vol;
}

void CSoundChannelGroup::setPause(bool newPaused)
{
	FMOD_RESULT result;
	result = chnlGrp->setPaused(newPaused);
	assert(result == FMOD_OK);
}

void CSoundChannelGroup::setPitch(float newPitch)
{
	FMOD_RESULT result;
	result = chnlGrp->setPitch(newPitch);
	assert(result == FMOD_OK);
}

void CSoundChannelGroup::addDSP(int index, CSoundDSP* dsp)
{
	FMOD_RESULT result;
	result = chnlGrp->addDSP(index, CSoundDSPAttorney::getFMODDSP(dsp));
	assert(result == FMOD_OK);
	//link wrapper classes
	DSPList::iterator it = DSPs.begin() + index;
	DSPs.insert(it, dsp);
}

void CSoundChannelGroup::removeDSP(CSoundDSP* dsp)
{
	FMOD_RESULT result;
	result = chnlGrp->removeDSP(CSoundDSPAttorney::getFMODDSP(dsp));
	assert(result == FMOD_OK);
	//internal list cleanup
	DSPList::iterator it = std::find(DSPs.begin(), DSPs.end(), dsp);
	DSPs.erase(it);
}

void CSoundChannelGroup::set3DAttrs(const Vect& pos, const Vect& vel)
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

	result = chnlGrp->set3DAttributes(&FMODpos, &FMODvel);
	assert(result == FMOD_OK);
}

float CSoundChannelGroup::GetPitch()
{
	float pitch;
	FMOD_RESULT result;
	result = chnlGrp->getPitch(&pitch);
	assert(result == FMOD_OK);
	return pitch;
}

bool CSoundChannelGroup::GetPaused()
{
	bool paused;
	FMOD_RESULT result;
	result = chnlGrp->getPaused(&paused);
	assert(result == FMOD_OK);
	return paused;
}

void CSoundChannelGroup::setPan(float newPan)
{
	FMOD_RESULT result;
	result = chnlGrp->setPan(newPan);
	assert(result == FMOD_OK);
}

void CSoundChannelGroup::incVol(float incAmt)
{
	float vol = GetVolume();
	setVol(vol + incAmt);
}

void CSoundChannelGroup::set3D(bool _3D)
{
	FMOD_RESULT result;
	//retrieve current FMOD mode first
	FMOD_MODE mode;
	result = chnlGrp->getMode(&mode);
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
		result = chnlGrp->setMode(mode);
		assert(result == FMOD_OK);
	}
	else
	{
		//unset the 3D flag
		mode = mode ^ FMOD_3D;
		//prevent double setting. This checks the bit in mode corresponding to FMOD_3D and makes sure it is unset. If it is not,
		//that means this function was called on a sound that already had FMOD_2D set instead.
		if (((mode >> 4) & 1) != 0)
		{
			throw std::runtime_error("Channel is already 2D!");
		}
		//then set 2D flag
		mode = mode | FMOD_2D;
		//making sure I'm setting the 2D bit(0x00000008) properly...
		assert(((mode >> 3) & 1) == 1);
		result = chnlGrp->setMode(mode);
		assert(result == FMOD_OK);
	}
}

void CSoundChannelGroup::set3DOcclusion(float directOcclusion, float reverbOcclusion)
{
	FMOD_RESULT result;
	result = chnlGrp->set3DOcclusion(directOcclusion, reverbOcclusion);
	assert(result == FMOD_OK);
}

FMOD::ChannelGroup* CSoundChannelGroup::getFMODGrp() const
{
	return chnlGrp;
}

CSoundChannelGroup::~CSoundChannelGroup()
{
	FMOD_RESULT result;
	result = chnlGrp->release();
	assert(result == FMOD_OK);
}