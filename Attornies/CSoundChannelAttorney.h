#ifndef C_SOUND_CHANNEL_ATTORNEY
#define C_SOUND_CHANNEL_ATTORNEY

class CSoundChannelGroup;

#include "CSoundChannel.h"

class CSoundChannelAttorney
{
public:
	class setPosCommand
	{
		friend class CChannelSetPositionCommand;
	private:
		static void setPos(CSoundChannel* chn, unsigned int newPos)
		{
			chn->setPos(newPos);
		}
	};
	class fastFwdCommand
	{
		friend class CChannelFastForwardCommand;
	private:
		static void fastFwd(CSoundChannel* chn, unsigned int fwdAmt)
		{
			chn->fastFwd(fwdAmt);
		}
	};
	class rwdCommand
	{
		friend class CChannelRewindCommand;
	private:
		static void rwd(CSoundChannel* chn, unsigned int rwdAmt)
		{
			chn->rwd(rwdAmt);
		}
	};
	class setGrpCommand
	{
		friend class CChannelSetGroupCommand;
	private:
		static void setChnlGrp(CSoundChannel* chn, CSoundChannelGroup* chnGrp)
		{
			chn->setChnlGrp(chnGrp);
		}
	};
};

#endif C_SOUND_CHANNEL_ATTORNEY