#include "CChannelSetVolumeCommand.h"
#include "CSoundChannelBase.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSetVolumeCommand::CChannelSetVolumeCommand(CSoundChannelBase* channel) : chnl(channel)
{
};

void CChannelSetVolumeCommand::Execute()
{
	CSoundChannelBaseAttorney::setVolCommand::setVol(chnl, vol);
}

void CChannelSetVolumeCommand::setNewVol(float newVol)
{
	vol = newVol;
}