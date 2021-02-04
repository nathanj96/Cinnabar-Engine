#include "CChannelAddDSPCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelAddDSPCommand::CChannelAddDSPCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelAddDSPCommand::Execute()
{
	CSoundChannelBaseAttorney::addDSPCommand::addDSP(chnl, index, dsp);
}

void CChannelAddDSPCommand::setNewDSP(CSoundDSP* newDSP)
{
	dsp = newDSP;
}

void CChannelAddDSPCommand::setNewIndex(int newInd)
{
	index = newInd;
}