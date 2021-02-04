#ifndef C_CHANNEL_SET_GROUP_COMMAND
#define C_CHANNEL_SET_GROUP_COMMAND

class CSoundChannel;
class CSoundChannelGroup;

#include "CAudioCommandBase.h"

class CChannelSetGroupCommand : public CAudioCommandBase
{
private:
	CSoundChannel* chnl;
	CSoundChannelGroup* newGrp;
public:
	CChannelSetGroupCommand() = delete;
	CChannelSetGroupCommand(const CChannelSetGroupCommand&) = delete;
	CChannelSetGroupCommand& operator=(const CChannelSetGroupCommand&) = delete;
	~CChannelSetGroupCommand() = default;

	CChannelSetGroupCommand(CSoundChannel* chn);

	virtual void Execute() override;

	//reset param to reuse command
	void setNewChannelGroup(CSoundChannelGroup* grp);
};

#endif C_CHANNEL_SET_GROUP_COMMAND