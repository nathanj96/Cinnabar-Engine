#ifndef C_CHANNEL_SET_POSITION_COMMAND
#define C_CHANNEL_SET_POSITION_COMMAND

class CSoundChannel;

#include "CAudioCommandBase.h"

class CChannelSetPositionCommand : public CAudioCommandBase
{
private:
	CSoundChannel* chnl;
	unsigned int pos;
public:
	CChannelSetPositionCommand() = delete;
	CChannelSetPositionCommand(const CChannelSetPositionCommand&) = delete;
	CChannelSetPositionCommand& operator=(const CChannelSetPositionCommand&) = delete;
	~CChannelSetPositionCommand() = default;

	CChannelSetPositionCommand(CSoundChannel* chn);

	virtual void Execute() override;

	//reset pos to reuse command
	void setNewPos(unsigned int newPos);
};

#endif C_CHANNEL_SET_POSITION_COMMAND