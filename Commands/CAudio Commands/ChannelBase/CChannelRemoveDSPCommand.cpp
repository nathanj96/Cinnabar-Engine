#include "CChannelRemoveDSPCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelRemoveDSPCommand::CChannelRemoveDSPCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelRemoveDSPCommand::Execute()
{
	CSoundChannelBaseAttorney::removeDSPCommand::removeDSP(chnl, dsp);
}

void CChannelRemoveDSPCommand::setNewDSP(CSoundDSP* newDSP)
{
	dsp = newDSP;
}