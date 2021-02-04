#ifndef C_SOUND_CHANNEL_BASE
#define C_SOUND_CHANNEL_BASE

//Contains common functions that can be applied to both CSoundChannels and CSoundChannelGroups

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"
#include "Vect.h"

#include <vector>

class CSoundDSP;
class CChannelSetVolumeCommand;
class CChannelIncrementVolumeCommand;
class CChannelPauseCommand;
class CChannelSetPanCommand;
class CChannelSetPitchCommand;
class CChannelAddDSPCommand;
class CChannelRemoveDSPCommand;
class CChannelSet3DCommand;
class CChannelSet3DAttributesCommand;
class CChannelSet3DOcclusionCommand;
class CSoundChannelBaseAttorney;

class CSoundChannelBase
{
	friend class CSoundChannelBaseAttorney;
private:

	virtual void setVol(float newVol) = 0;
	virtual void setPause(bool newPaused) = 0;
	virtual void setPan(float newPan) = 0;
	virtual void setPitch(float newPitch) = 0;
	virtual void addDSP(int index, CSoundDSP* dsp) = 0;
	virtual void removeDSP(CSoundDSP* dsp) = 0;
	virtual void incVol(float incAmt) = 0;
	virtual void set3DAttrs(const Vect& pos, const Vect& vel) = 0;
	virtual void set3D(bool _3D) = 0;
	virtual void set3DOcclusion(float directOcclusion, float reverbOcclusion) = 0;

protected:
	using DSPList = std::vector<CSoundDSP*>;
	DSPList DSPs;

	CChannelSetVolumeCommand* setVolCommandPtr;
	CChannelIncrementVolumeCommand* incVolCommandPtr;
	CChannelPauseCommand* pauseCommandPtr;
	CChannelSetPanCommand* setPanCommandPtr;
	CChannelSetPitchCommand* setPitchCommandPtr;
	CChannelAddDSPCommand* addDSPCommandPtr;
	CChannelRemoveDSPCommand* removeDSPCommandPtr;
	CChannelSet3DAttributesCommand* set3DAttrsCommandPtr;
	CChannelSet3DCommand* set3DCommandPtr;
	CChannelSet3DOcclusionCommand* set3DOccCommandPtr;

public:

	CSoundChannelBase();
	CSoundChannelBase(const CSoundChannelBase&) = delete;
	CSoundChannelBase& operator=(const CSoundChannelBase&) = delete;
	virtual ~CSoundChannelBase();

	//all virtual functions are ones that are different in CSoundChannels vs CSoundChannelGroups due to their
	//wrapped FMOD data being different, so need to redefine in each class

	//volume control

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::SetVolume(float newVol);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets a new volume for the CSoundChannel or CSoundChannelGroup. Defaults to 1.0.
	 * 			Negative levels will invert the signal, while levels above 1.0 will amplify it.
	 *
	 * \param 	newVol	The new volume to use.
	 **************************************************************************************************/

	void SetVolume(float newVol);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::IncrementVolume(float incAmt);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Increment volume by incAmt.
	 *
	 * \param 	incAmt	The amount to increment by.
	 **************************************************************************************************/

	void IncrementVolume(float incAmt);

	/**********************************************************************************************//**
	 * \fn	virtual float CSoundChannelBase::GetVolume() = 0;
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Retrieves the volume of the CSoundChannel or CSoundChannelGroup.
	 *
	 * \returns	The volume.
	 **************************************************************************************************/

	virtual float GetVolume() = 0;
	
	//Pause/unpause

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::SetPaused(bool newPaused);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets the paused state of the CSoundChannel or CSoundChannelGroup.
	 *
	 * \param 	newPaused	The new paused state to use.
	 * 						
	 * \note Calling this on a CSoundChannelGroup with unpaused CSoundChannels in it pauses the group,
	 * 		 but does not pause any of the channels in it.
	 **************************************************************************************************/

	void SetPaused(bool newPaused);

	/**********************************************************************************************//**
	 * \fn	virtual bool CSoundChannelBase::GetPaused() = 0;
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Retrieves the paused state of the CSoundChannel or CSoundChannelGroup.
	 *
	 * \returns	The paused state.
	 **************************************************************************************************/

	virtual bool GetPaused() = 0;

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::SetPan(float newPan);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets the pan of the CSoundChannel or CSoundChannelGroup, in the range [-1, 1]. -1 is full
	 * 			left, 0 is center, and 1 is full right.
	 *
	 * \param 	newPan	The new pan to use.
	 **************************************************************************************************/

	void SetPan(float newPan);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::SetPitch(float newPitch);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets the new pitch of the CSoundChannel or CSoundChannelGroup. Defaults to 1.0. Each
	 * 			multiple of 2 represents a new octave; for example, 2.0 is an octave up from 1.0, and
	 * 			0.5 is an octave down from 1.0.
	 *
	 * \param 	newPitch	The new pitch to use.
	 **************************************************************************************************/

	void SetPitch(float newPitch);

	/**********************************************************************************************//**
	 * \fn	virtual float CSoundChannelBase::GetPitch() = 0;
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Gets the pitch
	 *
	 * \returns	The pitch.
	 **************************************************************************************************/

	virtual float GetPitch() = 0;

	//DSP functions

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::AddDSP(int index, CSoundDSP* dsp);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Connects a DSP to the CSoundChannel or CSoundChannelGroup.
	 *
	 * \param 		  	index	The index of the DSP in the chain. 
	 * \param [in,out]	dsp  	The DSP to connect.
	 **************************************************************************************************/

	void AddDSP(int index, CSoundDSP* dsp);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::RemoveDSP(CSoundDSP* dsp);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Disconnects a DSP from the CSoundChannel or CSoundChannelGroup.
	 *
	 * \param [in,out]	dsp	The DSP to disconnect.
	 **************************************************************************************************/

	void RemoveDSP(CSoundDSP* dsp);

	//3D functions

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::Set3D(bool _3D);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets whether or not a CSoundChannel or CSoundChannelGroup will receive 3D effects.
	 * 			The initial 3D state of CSoundChannels is determined by that of the CSound that they play.
	 * 			CSoundChannelGroups are 2D by default.
	 *
	 * \param 	_3D The new 3D state.
	 **************************************************************************************************/

	void Set3D(bool _3D);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::Set3DAttributes(const Vect& pos, const Vect& vel);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets the position in 3D space of a CSoundChannel or CSoundChannelGroup. The velocity is
	 * 			used to calculate Doppler effect; if no velocity is present, no Doppler effect will be heard.
	 *
	 * \param 	pos	The new positionto use.
	 * \param 	vel	The new velocityto use.
	 * 				
	 * \note If this function is called on a CSoundChannel or CSoundChannelGroup that is not set to receive
	 * 		 3D effects, an error will be thrown.
	 **************************************************************************************************/

	void Set3DAttributes(const Vect& pos, const Vect& vel);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannelBase::Set3DOcclusion(float directOcclusion, float reverbOcclusion);
	 * \ingroup COMMONCHANNELMETHODS
	 * \brief	Sets the 3D occlusion factors for the direct path and the reverb path. Each defaults to 0
	 * 			and is in the range [0, 1], with 0 representing no occlusion and 1 representing full occlusion.
	 *
	 * \param 	directOcclusion	The new direct occlusion factor.
	 * \param 	reverbOcclusion	The new reverb occlusion factor.
	 **************************************************************************************************/

	void Set3DOcclusion(float directOcclusion, float reverbOcclusion);

};

#endif C_SOUND_CHANNEL_BASE