#include "CChannelRewindCommand.h"
#include "CSoundChannelAttorney.h"

CChannelRewindCommand::CChannelRewindCommand(CSoundChannel* chn) : chnl(chn)
{
};

void CChannelRewindCommand::Execute()
{
	CSoundChannelAttorney::rwdCommand::rwd(chnl, rwdAmt);
};

void CChannelRewindCommand::setNewRwdAmt(unsigned int newRwdAmt)
{
	rwdAmt = newRwdAmt;
}