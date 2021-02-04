#ifndef C_CHANNEL_FAST_FORWARD_COMMAND
#define C_CHANNEL_FAST_FORWARD_COMMAND

class CSoundChannel;

#include "CAudioCommandBase.h"

class CChannelFastForwardCommand : public CAudioCommandBase
{
private:
	CSoundChannel* chnl;
	unsigned int fwdAmt;
public:
	CChannelFastForwardCommand() = delete;
	CChannelFastForwardCommand(const CChannelFastForwardCommand&) = delete;
	CChannelFastForwardCommand& operator=(const CChannelFastForwardCommand&) = delete;
	~CChannelFastForwardCommand() = default;

	CChannelFastForwardCommand(CSoundChannel* chn);

	virtual void Execute() override;

	//reset inc amt to reuse command
	void setNewFwdAmt(unsigned int newFwdAmt);
};

#endif C_CHANNEL_FAST_FORWARD_COMMAND