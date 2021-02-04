#ifndef C_SOUND_CHANNEL_BASE_ATTORNEY
#define C_SOUND_CHANNEL_BASE_ATTORNEY

#include "CSoundChannelBase.h"

class CSoundChannelBaseAttorney
{
public:
	class setVolCommand
	{
		friend class CChannelSetVolumeCommand;
	private:
		static void setVol(CSoundChannelBase* chn, float vol)
		{
			chn->setVol(vol);
		}
	};
	class incVolCommand
	{
		friend class CChannelIncrementVolumeCommand;
	private:
		static void incVol(CSoundChannelBase* chn, float incAmt)
		{
			chn->incVol(incAmt);
		}
	};
	class pauseCommand
	{
		friend class CChannelPauseCommand;
	private:
		static void setPause(CSoundChannelBase* chn, bool paused)
		{
			chn->setPause(paused);
		}
	};
	class setPanCommand
	{
		friend class CChannelSetPanCommand;
	private:
		static void setPan(CSoundChannelBase* chn, float newPan)
		{
			chn->setPan(newPan);
		}
	};
	class setPitchCommand
	{
		friend class CChannelSetPitchCommand;
	private:
		static void setPitch(CSoundChannelBase* chn, float newPitch)
		{
			chn->setPitch(newPitch);
		}
	};
	class addDSPCommand
	{
		friend class CChannelAddDSPCommand;
	private:
		static void addDSP(CSoundChannelBase* chn, int index, CSoundDSP* dsp)
		{
			chn->addDSP(index, dsp);
		}
	};
	class removeDSPCommand
	{
		friend class CChannelRemoveDSPCommand;
	private:
		static void removeDSP(CSoundChannelBase* chn, CSoundDSP* dsp)
		{
			chn->removeDSP(dsp);
		}
	};
	class set3DCommand
	{
		friend class CChannelSet3DCommand;
	private:
		static void set3D(CSoundChannelBase* chn, bool _3D)
		{
			chn->set3D(_3D);
		}
	};
	class set3DAttrsCommand
	{
		friend class CChannelSet3DAttributesCommand;
	private:
		static void set3DAttrs(CSoundChannelBase* chn, const Vect& pos, const Vect& vel)
		{
			chn->set3DAttrs(pos, vel);
		}
	};
	class set3DOccCommand
	{
		friend class CChannelSet3DOcclusionCommand;
	private:
		static void set3DOcclusion(CSoundChannelBase* chn, float directOcc, float reverbOcc)
		{
			chn->set3DOcclusion(directOcc, reverbOcc);
		}
	};
};

#endif C_SOUND_CHANNEL_BASE_ATTORNEY