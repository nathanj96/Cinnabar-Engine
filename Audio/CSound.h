//Part of my personal project. This is the class for sound samples in Cinnabar Engine. Treated
//as assets. Playback controlled via CSoundChannels.

class CSoundChannel;
class CSoundPlayCommand;

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"

class CSoundAttorney;

class CSound
{
	friend class CSoundAttorney;
private:
	FMOD::Sound* snd;
	CSoundPlayCommand* playSoundCmdPtr;

	void playSound(bool startPaused, CSoundChannel* newChannel);
public:

	/**********************************************************************************************//**
	 * \fn	void CSound::Play(bool startPaused, CSoundChannel* newChannel);
	 * \ingroup CSOUNDMETHODS
	 * \brief	Plays the sound and connects it internally to newChannel. startPaused determines
	 * 			whether or not the channel will start paused. If the channel needs to be modified before
	 * 			the sound can be heard: play the sound with startPaused = true, modify the channel,
	 * 			then unpause it, like such:
	 *			\code
	 *				 {
	 *					//create sound and channel
	 *					CSound* snd = CSoundAssetManager::getSound("soundName");
	 *					CSoundChannel* chn = new CSoundChannel();
	 *					
	 *					//start playing it, paused at first
	 *					snd->Play(true, chn);
	 *					
	 *					//modify channel, for example raise its pitch:
	 *					chn->SetPitch(2.0f)
	 *					
	 *					//now unpause the channel
	 *					chn->SetPaused(false);
	 *				 }			
	 *			\endcode
	 *					
	 *			This will prevent the player from hearing the pitch change occur during playback.
	 *
	 * \param 		  	startPaused	Whether or not the CSoundChannel playing the sound should
	 * 								begin paused or not.
	 * \param			newChannel 	A CSoundChannel representing a newly playing instance of the
	 * 								CSound.
	 **************************************************************************************************/

	void Play(bool startPaused, CSoundChannel* newChannel);

	/**********************************************************************************************//**
	 * \fn	unsigned int CSound::getLength() const;
	 * \ingroup CSOUNDMETHODS
	 * \brief Returns the length of the sound file associated with this CSound.
	 *
	 * \returns	The length, in milliseconds.
	 **************************************************************************************************/

	unsigned int getLength() const;

	CSound() = delete;
	CSound(const CSound&) = delete;
	CSound& operator=(const CSound&) = delete;
	~CSound();

	//Set how many times a CSound will loop playback. Set to -1 for infinite looping.
	void SetNumLoops(int numLoops);
	int GetNumLoops() const;

	//Control what time in the sound loops begin and end at. Parameters are times in milliseconds
	void SetLoopStartAndEnd(unsigned int start, unsigned int end);

	/**********************************************************************************************//**
	 * \fn	void CSound::Set3D(bool _3D);
	 * \ingroup CSOUNDMETHODS
	 * \brief	Sets whether or not the CSound will have 3D effects applied to it. By default, all 
	 * 			CSounds are registered to receive 3D effects.
	 *
	 * \param 	Whether or not the sound should receive 3D effects.
	 **************************************************************************************************/

	void Set3D(bool _3D);

	/**********************************************************************************************//**
	 * \fn	void CSound::Set3DMinAndMaxAudibleDistance(float minDist, float maxDist);
	 *
	 * \brief	Applies only to 3D sounds. If the listener is less than minDist units away from the origin
	 * 			of the sound, they will hear it at full volume. As the listener moves outside of this range,
	 * 			the sound's volume will gradually decrease until the listener is more than maxDist units
	 * 			away from it, at which point no additional change in volume will be heard. Conversely, the
	 * 			sound will also get louder as the listener then moves closer to its origin.
	 *
	 * \param 	minDist	Within this range of the sound's origin, it is heard at full volume. Should be
	 * 					a radius.
	 * \param 	maxDist	The sound reaches its minimum volume if the listener is more than maxDist units 
	 * 					away from it. Should be a radius.
	 * \note	If the sound is not registered to receive 3D effects, calling this function on it will
	 * 			throw an error.
	 **************************************************************************************************/

	void Set3DMinAndMaxAudibleDistance(float minDist, float maxDist);

	CSound(const char* fileName);
};