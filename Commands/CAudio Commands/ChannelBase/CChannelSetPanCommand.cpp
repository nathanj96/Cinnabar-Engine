#include "CChannelSetPanCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSetPanCommand::CChannelSetPanCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelSetPanCommand::Execute()
{
	CSoundChannelBaseAttorney::setPanCommand::setPan(chnl, pan);
}

void CChannelSetPanCommand::setNewPan(float newPan)
{
	pan = newPan;
}