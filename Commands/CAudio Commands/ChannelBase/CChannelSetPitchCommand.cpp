#include "CChannelSetPitchCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSetPitchCommand::CChannelSetPitchCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelSetPitchCommand::Execute()
{
	CSoundChannelBaseAttorney::setPitchCommand::setPitch(chnl, pitch);
}

void CChannelSetPitchCommand::setNewPitch(float newPitch)
{
	pitch = newPitch;
}