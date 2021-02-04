#include "CChannelSet3DAttributesCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSet3DAttributesCommand::CChannelSet3DAttributesCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelSet3DAttributesCommand::Execute()
{
	CSoundChannelBaseAttorney::set3DAttrsCommand::set3DAttrs(chnl, pos, vel);
}

void CChannelSet3DAttributesCommand::setNewPosAndVel(const Vect& newPos, const Vect& newVel)
{
	pos = newPos;
	vel = newVel;
}