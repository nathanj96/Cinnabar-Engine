#ifndef C_CHANNEL_ADD_DSP_COMMAND
#define C_CHANNEL_ADD_DSP_COMMAND

class CSoundChannelBase;
class CSoundDSP;

#include "CAudioCommandBase.h"

class CChannelAddDSPCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	int index;
	CSoundDSP* dsp;
public:
	CChannelAddDSPCommand() = delete;
	CChannelAddDSPCommand(const CChannelAddDSPCommand&) = delete;
	CChannelAddDSPCommand& operator=(const CChannelAddDSPCommand&) = delete;
	~CChannelAddDSPCommand() = default;

	CChannelAddDSPCommand(CSoundChannelBase* chnl);

	virtual void Execute() override;

	//reset DSP val to reuse command
	void setNewDSP(CSoundDSP* newDSP);
	void setNewIndex(int newInd);
};

#endif C_CHANNEL_ADD_DSP_COMMAND