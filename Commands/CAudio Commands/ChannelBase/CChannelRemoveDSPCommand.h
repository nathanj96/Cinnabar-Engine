#ifndef C_CHANNEL_REMOVE_DSP_COMMAND
#define C_CHANNEL_REMOVE_DSP_COMMAND

class CSoundChannelBase;
class CSoundDSP;

#include "CAudioCommandBase.h"

class CChannelRemoveDSPCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	CSoundDSP* dsp;
public:
	CChannelRemoveDSPCommand() = delete;
	CChannelRemoveDSPCommand(const CChannelRemoveDSPCommand&) = delete;
	CChannelRemoveDSPCommand& operator=(const CChannelRemoveDSPCommand&) = delete;
	~CChannelRemoveDSPCommand() = default;

	CChannelRemoveDSPCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset DSP to reuse command
	void setNewDSP(CSoundDSP* newDSP);
};

#endif C_CHANNEL_REMOVE_DSP_COMMAND