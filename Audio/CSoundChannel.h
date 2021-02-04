#ifndef C_SOUND_CHANNEL
#define C_SOUND_CHANNEL

class CSound;
class CSoundDSP;
class CSoundChannelAttorney;
class CChannelSetPositionCommand;
class CChannelFastForwardCommand;
class CChannelRewindCommand;
class CChannelSetGroupCommand;
class CSoundChannelGroup;

#include "CSoundChannelBase.h"
#include "Vect.h"

#include <vector>

class CSoundChannel : public CSoundChannelBase
{
	friend class CSoundChannelAttorney;
private:
	FMOD::Channel* chnl;
	CSound* soundPlaying;

	CChannelSetPositionCommand* setPosCommandPtr;
	CChannelFastForwardCommand* fastFwdCommandPtr;
	CChannelRewindCommand* rwdCommandPtr;
	CChannelSetGroupCommand* setGrpCommandPtr;

	virtual void setVol(float newVol) override;
	virtual void setPause(bool newPaused) override;
	virtual void setPan(float newPan) override;
	virtual void setPitch(float newPitch) override;
	virtual void addDSP(int index, CSoundDSP* dsp) override;
	virtual void removeDSP(CSoundDSP* dsp) override;
	virtual void incVol(float incAmt) override;

	virtual void set3D(bool _3D) override;
	virtual void set3DAttrs(const Vect& pos, const Vect& vel) override;
	virtual void set3DOcclusion(float directOcclusion, float reverbOcclusion) override;

	void setChnlGrp(CSoundChannelGroup* newGrp);

	void setPos(unsigned int newPos);
	void fastFwd(unsigned int amt);
	void rwd(unsigned int amt);
public:
	CSoundChannel();
	CSoundChannel(const CSoundChannel&) = delete;
	CSoundChannel& operator=(const CSoundChannel&) = delete;
	~CSoundChannel();

	virtual float GetVolume() override;
	virtual bool GetPaused() override;
	virtual float GetPitch() override;

	/**********************************************************************************************//**
	 * \fn	void CSoundChannel::SetPosition(unsigned int newPosition);
	 * \ingroup CSOUNDCHANNELMETHODS
	 * \brief	Sets the playback position of the channel.
	 *
	 * \param 	newPosition	The new position, in milliseconds.
	 **************************************************************************************************/

	void SetPosition(unsigned int newPosition);

	/**********************************************************************************************//**
	 * \fn	unsigned int CSoundChannel::GetPosition() const;
	 * \ingroup CSOUNDCHANNELMETHODS
	 * \brief	Retrieves the playback position of the channel.
	 *
	 * \returns	The position, in milliseconds.
	 **************************************************************************************************/

	unsigned int GetPosition() const;

	/**********************************************************************************************//**
	 * \fn	void CSoundChannel::FastForward(unsigned int amt);
	 * \ingroup CSOUNDCHANNELMETHODS
	 * \brief	Advance playback of the sound by amt. If this would push the playback position past the end
	 * 			of the sound, it snaps it to the end of the sound instead.
	 *
	 * \param 	amt	The time, in milliseconds, to advance playback by.
	 **************************************************************************************************/

	void FastForward(unsigned int amt);

	/**********************************************************************************************//**
	 * \fn	void CSoundChannel::Rewind(unsigned int amt);
	 * \ingroup CSOUNDCHANNELMETHODS
	 * \brief	Reverse playback of the sound by amt. If this would push the playback position to before the
	 * 			beginning of the sound, it snaps it to the beginning of the sound instead.
	 *
	 * \param 	amt	The time, in milliseconds, to reverse playback by.
	 **************************************************************************************************/

	void Rewind(unsigned int amt);

	int GetIndex() const;

	/**********************************************************************************************//**
	 * \fn	void CSoundChannel::SetChannelGroup(CSoundChannelGroup* newGrp);
	 * \ingrop CSOUNDCHANNELMETHODS
	 * \brief	Assigns the CSoundChannel to a new CSoundChannelGroup. 
	 *
	 * \param		newGrp	The new group for the CSoundChannel.
	 * 						
	 * \note Each CSoundChannel can only be in one CSoundChannelGroup at a time. If this channel is already
	 * 		 in a group, it will be removed from its old group before it is assigned to newGrp.
	 **************************************************************************************************/

	void SetChannelGroup(CSoundChannelGroup* newGrp);

	//probably should make these private later
	void setFMODChannel(FMOD::Channel* newChnl);
	void setSound(CSound* newSound);

	//debug
	FMOD::Channel* getFMODChannel() const;
};

#endif C_SOUND_CHANNEL