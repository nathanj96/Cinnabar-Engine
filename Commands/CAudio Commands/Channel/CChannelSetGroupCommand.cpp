#include "CChannelSetGroupCommand.h"
#include "CSoundChannelAttorney.h"

CChannelSetGroupCommand::CChannelSetGroupCommand(CSoundChannel* chn) : chnl(chn)
{
};

void CChannelSetGroupCommand::Execute()
{
	CSoundChannelAttorney::setGrpCommand::setChnlGrp(chnl, newGrp);
}

void CChannelSetGroupCommand::setNewChannelGroup(CSoundChannelGroup* grp)
{
	newGrp = grp;
}