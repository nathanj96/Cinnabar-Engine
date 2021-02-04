#include "CChannelSetPositionCommand.h"
#include "CSoundChannelAttorney.h"

CChannelSetPositionCommand::CChannelSetPositionCommand(CSoundChannel* chn) : chnl(chn)
{
}

void CChannelSetPositionCommand::Execute()
{
	CSoundChannelAttorney::setPosCommand::setPos(chnl, pos);
}

void CChannelSetPositionCommand::setNewPos(unsigned int newPos)
{
	pos = newPos;
}