#include "CChannelIncrementVolumeCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelIncrementVolumeCommand::CChannelIncrementVolumeCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelIncrementVolumeCommand::Execute()
{
	CSoundChannelBaseAttorney::incVolCommand::incVol(chnl, incAmt);
}

void CChannelIncrementVolumeCommand::setNewIncAmt(float newIncAmt)
{
	incAmt = newIncAmt;
}