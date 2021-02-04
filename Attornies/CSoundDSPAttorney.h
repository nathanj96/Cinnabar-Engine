#ifndef C_SOUND_DSP_ATTORNEY
#define C_SOUND_DSP_ATTORNEY

class CSoundChannel;

#include "CSoundDSP.h"

class CSoundDSPAttorney
{
	//give CSoundChannel access to the CSoundDSP's FMOD::DSP data member so the CSoundChannel can connect it
	//to its FMOD::Channel. Want to leave it private otherwise
	friend class CSoundChannel;
	friend class CSoundChannelGroup;
private:
	static FMOD::DSP* getFMODDSP(CSoundDSP* cDSP)
	{
		return cDSP->dsp;
	}
};

#endif C_SOUND_DSP_ATTORNEY
