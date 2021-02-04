#ifndef C_CHANNEL_SET_VOLUME_COMMAND
#define C_CHANNEL_SET_VOLUME_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelSetVolumeCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	float vol;
public:
	CChannelSetVolumeCommand() = delete;
	CChannelSetVolumeCommand(const CChannelSetVolumeCommand&) = delete;
	CChannelSetVolumeCommand& operator=(const CChannelSetVolumeCommand&) = delete;
	~CChannelSetVolumeCommand() = default;

	CChannelSetVolumeCommand(CSoundChannelBase* channel);
	virtual void Execute() override;

	//allow resetting of parameters
	void setNewVol(float newVol);
};

#endif C_CHANNEL_SET_VOLUME_COMMAND