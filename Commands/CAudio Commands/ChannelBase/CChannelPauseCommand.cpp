#include "CChannelPauseCommand.h"
#include "CSoundChannelBase.h"
#include "CSoundChannelBaseAttorney.h"

CChannelPauseCommand::CChannelPauseCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelPauseCommand::Execute()
{
	CSoundChannelBaseAttorney::pauseCommand::setPause(chnl, paused);
}

void CChannelPauseCommand::setNewPaused(bool newPaused)
{
	paused = newPaused;
}