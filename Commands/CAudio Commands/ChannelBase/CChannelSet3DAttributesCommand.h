#ifndef C_CHANNEL_SET_3D_ATTRIBUTES_COMMAND
#define C_CHANNEL_SET_3D_ATTRIBUTES_COMMAND

class CSoundChannelBase;

#include "CAudioCommandBase.h"
#include "Vect.h"

class CChannelSet3DAttributesCommand : public CAudioCommandBase
{
private:
	CSoundChannelBase* chnl;
	Vect pos;
	Vect vel;
public:
	CChannelSet3DAttributesCommand() = delete;
	CChannelSet3DAttributesCommand(const CChannelSet3DAttributesCommand&) = delete;
	CChannelSet3DAttributesCommand& operator=(const CChannelSet3DAttributesCommand&) = delete;
	~CChannelSet3DAttributesCommand() = default;

	CChannelSet3DAttributesCommand(CSoundChannelBase* chn);

	virtual void Execute() override;

	//reset params to reuse command
	void setNewPosAndVel(const Vect& newPos, const Vect& newVel);
};

#endif C_CHANNEL_SET_3D_ATTRIBUTES_COMMAND