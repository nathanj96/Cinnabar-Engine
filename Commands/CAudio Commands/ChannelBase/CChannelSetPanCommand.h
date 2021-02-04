#ifndef C_SOUND_SET_PAN_COMMAND
#define C_SOUND_SET_PAN_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelSetPanCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	float pan;
public:
	CChannelSetPanCommand() = delete;
	CChannelSetPanCommand(const CChannelSetPanCommand&) = delete;
	CChannelSetPanCommand& operator=(const CChannelSetPanCommand&) = delete;
	~CChannelSetPanCommand() = default;

	CChannelSetPanCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset pan to reuse command
	void setNewPan(float newPan);
};

#endif C_SOUND_SET_PAN_COMMAND