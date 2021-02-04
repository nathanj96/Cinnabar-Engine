#ifndef C_CHANNEL_SET_3D_OCCLUSION_COMMAND
#define C_CHANNEL_SET_3D_OCCLUSION_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelSet3DOcclusionCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	float directOcc;
	float reverbOcc;
public:
	CChannelSet3DOcclusionCommand() = delete;
	CChannelSet3DOcclusionCommand(const CChannelSet3DOcclusionCommand&) = delete;
	CChannelSet3DOcclusionCommand& operator=(const CChannelSet3DOcclusionCommand&) = delete;
	~CChannelSet3DOcclusionCommand() = default;

	CChannelSet3DOcclusionCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset params to reuse command
	void setDirectOcclusion(float newOcc);
	void setReverbOcclusion(float newOcc);
};

#endif C_CHANNEL_SET_3D_OCCLUSION_COMMAND