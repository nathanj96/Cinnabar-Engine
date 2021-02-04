#ifndef C_CHANNEL_REWIND_COMMAND
#define C_CHANNEL_REWIND_COMMAND

class CSoundChannel;

#include "CAudioCommandBase.h"

class CChannelRewindCommand : public CAudioCommandBase
{
private:
	CSoundChannel* chnl;
	unsigned int rwdAmt;
public:
	CChannelRewindCommand() = delete;
	CChannelRewindCommand(const CChannelRewindCommand&) = delete;
	CChannelRewindCommand& operator=(const CChannelRewindCommand&) = delete;
	~CChannelRewindCommand() = default;

	CChannelRewindCommand(CSoundChannel* chn);

	virtual void Execute() override;

	//reset rwd amt to reuse command
	void setNewRwdAmt(unsigned int newRwdAmt);
};

#endif C_CHANNEL_REWIND_COMMAND