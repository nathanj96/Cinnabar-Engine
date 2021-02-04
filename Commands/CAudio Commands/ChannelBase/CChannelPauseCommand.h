#ifndef C_CHANNEL_PAUSE_COMMAND
#define C_CHANNEL_PAUSE_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelPauseCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	bool paused;
public:
	CChannelPauseCommand() = delete;
	CChannelPauseCommand(const CChannelPauseCommand&) = delete;
	CChannelPauseCommand& operator=(const CChannelPauseCommand&) = delete;
	~CChannelPauseCommand() = default;

	CChannelPauseCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset bool val to reuse command
	void setNewPaused(bool newPaused);
};

#endif C_CHANNEL_PAUSE_COMMAND