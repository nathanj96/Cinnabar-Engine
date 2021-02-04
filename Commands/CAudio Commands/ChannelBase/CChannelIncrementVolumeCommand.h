#ifndef C_CHANNEL_INCREMENT_VOLUME_COMMAND
#define C_CHANNEL_INCREMENT_VOLUME_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelIncrementVolumeCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	float incAmt;
public:
	CChannelIncrementVolumeCommand() = delete;
	CChannelIncrementVolumeCommand(const CChannelIncrementVolumeCommand&) = delete;
	CChannelIncrementVolumeCommand& operator=(const CChannelIncrementVolumeCommand&) = delete;
	~CChannelIncrementVolumeCommand() = default;

	CChannelIncrementVolumeCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset inc amt to reuse command
	void setNewIncAmt(float newIncAmt);
};

#endif C_CHANNEL_INCREMENT_VOLUME_COMMAND