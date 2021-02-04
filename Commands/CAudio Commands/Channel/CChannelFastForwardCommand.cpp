#include "CChannelFastForwardCommand.h"
#include "CSoundChannelAttorney.h"

CChannelFastForwardCommand::CChannelFastForwardCommand(CSoundChannel* chn) : chnl(chn)
{
};

void CChannelFastForwardCommand::Execute()
{
	CSoundChannelAttorney::fastFwdCommand::fastFwd(chnl, fwdAmt);
}

void CChannelFastForwardCommand::setNewFwdAmt(unsigned int newFwdAmt)
{
	fwdAmt = newFwdAmt;
}