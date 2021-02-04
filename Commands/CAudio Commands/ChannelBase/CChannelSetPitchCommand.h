#ifndef C_CHANNEL_SET_PITCH_COMMAND
#define C_CHANNEL_SET_PITCH_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelSetPitchCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	float pitch;
public:
	CChannelSetPitchCommand() = delete;
	CChannelSetPitchCommand(const CChannelSetPitchCommand&) = delete;
	CChannelSetPitchCommand& operator=(const CChannelSetPitchCommand&) = delete;
	~CChannelSetPitchCommand() = default;

	CChannelSetPitchCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset pitch to reuse command
	void setNewPitch(float newPitch);
};

#endif C_CHANNEL_SET_PITCH_COMMAND