#ifndef C_AUDIO_MANAGER
#define C_AUDIO_MANAGER

class CSound;
class CSoundChannel;
class CAudioManagerAttorney;

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"
#include "CSoundDSP.h"
#include "CSound3DReverb.h"
#include "Vect.h"

class CAudioManager
{
	friend class CAudioManagerAttorney;
private:
	static void Terminate();
	static void Initialize();
//briefly making this public for debug purposes
public:
	//Main system object for FMOD
	FMOD::System* sys;

	//singleton pattern
	static CAudioManager* CAudioManagerInstance;

private:
	CAudioManager() = default;
	CAudioManager(const CAudioManager&) = delete;
	CAudioManager& operator=(const CAudioManager&) = delete;
	~CAudioManager();

	static CAudioManager& Instance()
	{
		if (!CAudioManagerInstance)
			CAudioManagerInstance = new CAudioManager;

		return *CAudioManagerInstance;
	}

	//Internal handling of sound playback
	void playFMODSoundInternal(FMOD::Sound* sound, bool startPaused, CSoundChannel* newChannel);

	FMOD_RESULT createFMODSoundInternal(const char* fileName, FMOD::Sound** sound);
	FMOD_RESULT createFMODDSPInternal(CSoundDSP::DSPTypes type, FMOD::DSP** dsp);
	FMOD_RESULT createFMODReverb3DInternal(CSound3DReverb::ReverbTypes type, FMOD::Reverb3D** rvb);
	FMOD_RESULT createFMODGeometryInternal(int maxPolys, int maxVerts, FMOD::Geometry** geo);
	FMOD_RESULT createFMODChannelGroupInternal(FMOD::ChannelGroup** chnlGrp);

	//where is the 3D listener in world space right now? 
	Vect listenerPos;
	//calculated in Update
	Vect listenerLastPos;
	Vect listenerFwd;
	Vect listenerUp;

	static void Update();

public:
	static void PlayFMODSound(FMOD::Sound* sound, bool startPaused, CSoundChannel* newChannel);
	static FMOD_RESULT CreateFMODSound(const char* fileName, FMOD::Sound** sound);
	static FMOD_RESULT CreateFMODDSP(CSoundDSP::DSPTypes type, FMOD::DSP** dsp);
	static FMOD_RESULT CreateFMODReverb3D(CSound3DReverb::ReverbTypes type, FMOD::Reverb3D** rvb);
	static FMOD_RESULT CreateFMODGeometry(int maxPolys, int maxVerts, FMOD::Geometry** geo);
	static FMOD_RESULT CreateFMODChannelGroup(FMOD::ChannelGroup** chnlGrp);
	static void Set3DSettings(float dopplerScale, float distanceFactor, float rolloffScale);

	//static void set3DAttsToTrack(Vect* pos, Vect* fwd, Vect* up);
};

#endif C_AUDIO_MANAGER