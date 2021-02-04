#ifndef C_CHANNEL_SET_3D_COMMAND
#define C_CHANNEL_SET_3D_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"

class CChannelSet3DCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	bool set3D;
public:
	CChannelSet3DCommand() = delete;
	CChannelSet3DCommand(const CChannelSet3DCommand&) = delete;
	CChannelSet3DCommand& operator=(const CChannelSet3DCommand&) = delete;
	~CChannelSet3DCommand() = default;

	CChannelSet3DCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset bool to reuse command
	void setNew3D(bool new3D);
};

#endif C_CHANNEL_SET_3D_COMMAND