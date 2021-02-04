#include "CChannelSet3DCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSet3DCommand::CChannelSet3DCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelSet3DCommand::Execute()
{
	CSoundChannelBaseAttorney::set3DCommand::set3D(chnl, set3D);
}

void CChannelSet3DCommand::setNew3D(bool new3D)
{
	set3D = new3D;
}