#include "CChannelSet3DOcclusionCommand.h"
#include "CSoundChannelBaseAttorney.h"

CChannelSet3DOcclusionCommand::CChannelSet3DOcclusionCommand(CSoundChannelBase* chn) : chnl(chn)
{
};

void CChannelSet3DOcclusionCommand::Execute()
{
	CSoundChannelBaseAttorney::set3DOccCommand::set3DOcclusion(chnl, directOcc, reverbOcc);
}

void CChannelSet3DOcclusionCommand::setDirectOcclusion(float newOcc)
{
	directOcc = newOcc;
}

void CChannelSet3DOcclusionCommand::setReverbOcclusion(float newOcc)
{
	reverbOcc = newOcc;
}

