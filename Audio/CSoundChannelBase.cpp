#include "CSoundChannelBase.h"
#include "CChannelSetVolumeCommand.h"
#include "CChannelIncrementVolumeCommand.h"
#include "CChannelPauseCommand.h"
#include "CChannelSetPanCommand.h"
#include "CChannelSetPitchCommand.h"
#include "CChannelAddDSPCommand.h"
#include "CChannelRemoveDSPCommand.h"
#include "CChannelSet3DCommand.h"
#include "CChannelSet3DAttributesCommand.h"
#include "CChannelSet3DOcclusionCommand.h"

#include "SceneAttorney.h"

CSoundChannelBase::CSoundChannelBase()
{
	setVolCommandPtr = new CChannelSetVolumeCommand(this);
	incVolCommandPtr = new CChannelIncrementVolumeCommand(this);
	pauseCommandPtr = new CChannelPauseCommand(this);
	setPanCommandPtr = new CChannelSetPanCommand(this);
	setPitchCommandPtr = new CChannelSetPitchCommand(this);
	addDSPCommandPtr = new CChannelAddDSPCommand(this);
	removeDSPCommandPtr = new CChannelRemoveDSPCommand(this);
	set3DCommandPtr = new CChannelSet3DCommand(this);
	set3DAttrsCommandPtr = new CChannelSet3DAttributesCommand(this);
	set3DOccCommandPtr = new CChannelSet3DOcclusionCommand(this);
}

void CSoundChannelBase::SetVolume(float newVol)
{
	setVolCommandPtr->setNewVol(newVol);
	SceneAttorney::toCAudio::submitCSoundCommand(setVolCommandPtr);
}

void CSoundChannelBase::IncrementVolume(float incAmt)
{
	incVolCommandPtr->setNewIncAmt(incAmt);
	SceneAttorney::toCAudio::submitCSoundCommand(incVolCommandPtr);
}

void CSoundChannelBase::AddDSP(int index, CSoundDSP* dsp)
{
	addDSPCommandPtr->setNewDSP(dsp);
	addDSPCommandPtr->setNewIndex(index);
	SceneAttorney::toCAudio::submitCSoundCommand(addDSPCommandPtr);
}

void CSoundChannelBase::RemoveDSP(CSoundDSP* dsp)
{
	removeDSPCommandPtr->setNewDSP(dsp);
	SceneAttorney::toCAudio::submitCSoundCommand(removeDSPCommandPtr);
}

void CSoundChannelBase::SetPaused(bool newPaused)
{
	pauseCommandPtr->setNewPaused(newPaused);
	SceneAttorney::toCAudio::submitCSoundCommand(pauseCommandPtr);
}

void CSoundChannelBase::SetPan(float newPan)
{
	setPanCommandPtr->setNewPan(newPan);
	SceneAttorney::toCAudio::submitCSoundCommand(setPanCommandPtr);
}

void CSoundChannelBase::SetPitch(float newPitch)
{
	setPitchCommandPtr->setNewPitch(newPitch);
	SceneAttorney::toCAudio::submitCSoundCommand(setPitchCommandPtr);
}

void CSoundChannelBase::Set3D(bool _3D)
{
	set3DCommandPtr->setNew3D(_3D);
	SceneAttorney::toCAudio::submitCSoundCommand(set3DCommandPtr);
}

void CSoundChannelBase::Set3DAttributes(const Vect& pos, const Vect& vel)
{
	set3DAttrsCommandPtr->setNewPosAndVel(pos, vel);
	SceneAttorney::toCAudio::submitCSoundCommand(set3DAttrsCommandPtr);
}

void CSoundChannelBase::Set3DOcclusion(float directOcclusion, float reverbOcclusion)
{
	set3DOccCommandPtr->setDirectOcclusion(directOcclusion);
	set3DOccCommandPtr->setReverbOcclusion(reverbOcclusion);
	SceneAttorney::toCAudio::submitCSoundCommand(set3DOccCommandPtr);
}

CSoundChannelBase::~CSoundChannelBase()
{
	delete setVolCommandPtr;
	setVolCommandPtr = nullptr;
	delete incVolCommandPtr;
	incVolCommandPtr = nullptr;
	delete pauseCommandPtr;
	pauseCommandPtr = nullptr;
	delete setPanCommandPtr;
	setPanCommandPtr = nullptr;
	delete setPitchCommandPtr;
	setPitchCommandPtr = nullptr;
	delete addDSPCommandPtr;
	addDSPCommandPtr = nullptr;
	delete removeDSPCommandPtr;
	removeDSPCommandPtr = nullptr;
	delete set3DCommandPtr;
	set3DCommandPtr = nullptr;
	delete set3DAttrsCommandPtr;
	set3DAttrsCommandPtr = nullptr;
	delete set3DOccCommandPtr;
	set3DOccCommandPtr = nullptr;
}