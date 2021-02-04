#include "CAudioManager.h"
#include "CSound.h"
#include "CSoundChannel.h"
#include "CSoundChannelGroup.h"
#include "ScreenLog.h"
#include "TimeManager.h"
#include "ScreenLog.h"
#include "Matrix.h"
#include "SceneManager.h"
#include "Camera.h"
#include "ScreenLog.h"
#include <cmath>

CAudioManager* CAudioManager::CAudioManagerInstance = nullptr;

void CAudioManager::Initialize()
{
	//create the system object,
	FMOD_RESULT result;

	result = FMOD::System_Create(&Instance().sys);
	assert(result == FMOD_OK);

	//then initialize it. The 1st parameter specifies the maximum amount of channels possible.
	//The second and third ones are unimportant for now, but I think I'll need to revisit the second
	//one when I start to implement 3D sound.
	result = Instance().sys->init(512, FMOD_INIT_3D_RIGHTHANDED | FMOD_INIT_CHANNEL_LOWPASS, 0);
	assert(result == FMOD_OK);

	//testing doppler
	Instance().Set3DSettings(1.0f, 1.0f, 1.0f);

	Instance().listenerPos = Vect(0.0f, 0.0f, 0.0f);
	Instance().listenerLastPos = Vect(0.0f, 0.0f, 0.0f);
	Instance().listenerFwd = Vect(0.0f, 0.0f, 0.0f);
	Instance().listenerUp = Vect(0.0f, 0.0f, 0.0f);
}

void CAudioManager::Update()
{
	FMOD_RESULT result;

	Camera* curCam = SceneManager::getCurrentCamera();
	curCam->getPos(Instance().listenerPos);
	curCam->getDir(Instance().listenerFwd);
	curCam->getUp(Instance().listenerUp);
	//ScreenLog::Add("Listener pos: %f, %f, %f", Instance().listenerPos.X(), Instance().listenerPos.Y(), Instance().listenerPos.Z());

	//update system 3D listener attributes. System update() function calculates 3D sound effects based
	//on these changes, so make them first
	//calculate the velocity of the listener - needs to be converted to units per SECOND before using
	float deltaTime = TimeManager::getFrameTime();
	//ScreenLog::Add("Delta time: %f", deltaTime);
	Vect vel = (Instance().listenerPos - Instance().listenerLastPos) * deltaTime;
	//ScreenLog::Add("Velocity vect: (%f, %f, %f)", vel.X(), vel.Y(), vel.Z());
	//current pos will be "last pos" next frame
	Instance().listenerLastPos = Instance().listenerPos;

	//now we get to convert all 4 to FMOD vectors.............Need to rotate the vectors first so that they are in the orientation
	//that +x = right, per the requirements of FMOD
	FMOD_VECTOR FMODpos;
	//Vect posRot = (*Instance().listenerPos) * Matrix(ROT_Y, -3.14159f);
	FMODpos.x = Instance().listenerPos.X();
	FMODpos.y = Instance().listenerPos.Y();
	FMODpos.z = Instance().listenerPos.Z();
	//FMODpos.x = posRot.X();
	//FMODpos.y = posRot.Y();
	//FMODpos.z = posRot.Z();

	FMOD_VECTOR FMODvel;
	//Vect velRot = vel * Matrix(ROT_Y, -3.14159f);
	//if velocity is too high, treat it as no movement to not cause very weird sound effects
	FMODvel.x = vel.X();
	//if (abs(FMODvel.x) >= 10000.0f)
	//{
	//	FMODvel.x = 0.0f;
	//}
	FMODvel.y = vel.Y();
	//if (abs(FMODvel.y) >= 10000.0f)
	//{
	//	FMODvel.y = 0.0f;
	//}
	FMODvel.z = vel.Z();
	//if (abs(FMODvel.z) >= 10000.0f)
	//{
	//	FMODvel.z = 0.0f;
	//}
	//FMODvel.x = velRot.X();
	//FMODvel.y = velRot.Y();
	//FMODvel.z = velRot.Z();

	FMOD_VECTOR FMODfwd;
	//Vect fwdRot = (*Instance().listenerFwd) * Matrix(ROT_Y, -3.14159f);
	FMODfwd.x = Instance().listenerFwd.X();
	FMODfwd.y = Instance().listenerFwd.Y();
	FMODfwd.z = Instance().listenerFwd.Z();
	//FMODfwd.x = fwdRot.X();
	//FMODfwd.y = fwdRot.Y();
	//FMODfwd.z = fwdRot.Z();

	FMOD_VECTOR FMODup;
	//Vect upRot = (*Instance().listenerUp) * Matrix(ROT_Y, -3.14159f);
	FMODup.x = Instance().listenerUp.X();
	FMODup.y = Instance().listenerUp.Y();
	FMODup.z = Instance().listenerUp.Z();
	//FMODup.x = upRot.X();
	//FMODup.y = upRot.Y();
	//FMODup.z = upRot.Z();

	//noooooow set the attributes...
	result = Instance().sys->set3DListenerAttributes(0, &FMODpos, &FMODvel, &FMODfwd, &FMODup);
	assert(result == FMOD_OK);

	//FMOD system update - Required according to FMOD API
	result = Instance().sys->update();
	assert(result == FMOD_OK);
}

FMOD_RESULT CAudioManager::CreateFMODSound(const char* fileName, FMOD::Sound** sound)
{
	return Instance().createFMODSoundInternal(fileName, sound);
}

FMOD_RESULT CAudioManager::createFMODSoundInternal(const char* fileName, FMOD::Sound** sound)
{
	FMOD_RESULT result;
	result = Instance().sys->createSound(fileName, FMOD_3D | FMOD_LOOP_NORMAL, 0, sound);
	assert(result == FMOD_OK);
	return result;
}

FMOD_RESULT CAudioManager::CreateFMODDSP(CSoundDSP::DSPTypes type, FMOD::DSP** dsp)
{
	return Instance().createFMODDSPInternal(type, dsp);
}

FMOD_RESULT CAudioManager::createFMODDSPInternal(CSoundDSP::DSPTypes type, FMOD::DSP** dsp)
{
	FMOD_RESULT result;
	//switch statement not ideal, but only called once on creation
	switch (type)
	{
	case(CSoundDSP::DSPTypes::Mixer):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_MIXER, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Chorus):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_CHORUS, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Echo):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_ECHO, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Flange):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_FLANGE, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Highpass):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Lowpass):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_LOWPASS, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Tremolo):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_TREMOLO, dsp);
		break;
	}
	case(CSoundDSP::DSPTypes::Distortion):
	{
		result = Instance().sys->createDSPByType(FMOD_DSP_TYPE_DISTORTION, dsp);
		break;
	}
	default:
	{
		throw std::runtime_error("Invalid DSP type requested!");
	}
	};
	assert(result == FMOD_OK);
	return result;
}

FMOD_RESULT CAudioManager::CreateFMODReverb3D(CSound3DReverb::ReverbTypes type, FMOD::Reverb3D** rvb)
{
	return Instance().createFMODReverb3DInternal(type, rvb);
}

FMOD_RESULT CAudioManager::createFMODReverb3DInternal(CSound3DReverb::ReverbTypes type, FMOD::Reverb3D** rvb)
{
	FMOD_RESULT result;
	//switch statement not ideal, but only called once on creation
	switch (type)
	{
	case(CSound3DReverb::ReverbTypes::Alley):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_ALLEY;
		(*rvb)->setProperties(&prop);
		break;
	}
	case(CSound3DReverb::ReverbTypes::Auditorium):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_AUDITORIUM;
		(*rvb)->setProperties(&prop);
		break;
	}
	case(CSound3DReverb::ReverbTypes::Cave):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CAVE;
		(*rvb)->setProperties(&prop);
		break;
	}
	case(CSound3DReverb::ReverbTypes::ConcertHall):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL;
		(*rvb)->setProperties(&prop);
		break;
	}
	case(CSound3DReverb::ReverbTypes::PaddedCell):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_PADDEDCELL;
		(*rvb)->setProperties(&prop);
		break;
	}
	case(CSound3DReverb::ReverbTypes::Underwater):
	{
		result = Instance().sys->createReverb3D(rvb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
		(*rvb)->setProperties(&prop);
		break;
	}
	default:
	{
		throw std::runtime_error("Invalid reverb type requested!");
	}
	}
	assert(result == FMOD_OK);
	return result;
}

FMOD_RESULT CAudioManager::CreateFMODGeometry(int maxPolys, int maxVerts, FMOD::Geometry** geo)
{
	return Instance().createFMODGeometryInternal(maxPolys, maxVerts, geo);
}

FMOD_RESULT CAudioManager::createFMODGeometryInternal(int maxPolys, int maxVerts, FMOD::Geometry** geo)
{
	FMOD_RESULT result;
	result = Instance().sys->createGeometry(maxPolys, maxVerts, geo);
	assert(result == FMOD_OK);
	return result;
}

void CAudioManager::PlayFMODSound(FMOD::Sound* sound, bool startPaused, CSoundChannel* newChannel)
{
	Instance().playFMODSoundInternal(sound, startPaused, newChannel);
}

void CAudioManager::playFMODSoundInternal(FMOD::Sound* sound, bool startPaused, CSoundChannel* newChannel)
{
	FMOD::Channel* FMODchnl;
	FMOD_RESULT result;
	result = Instance().sys->playSound(sound, 0, startPaused, &FMODchnl);
	assert(result == FMOD_OK);
	newChannel->setFMODChannel(FMODchnl);

	//debug
	int chnInd;
	result = FMODchnl->getIndex(&chnInd);
	assert(result == FMOD_OK);
	ScreenLog::Add("Playing on channel %d", chnInd);
}

//void CAudioManager::set3DAttsToTrack(Vect* pos, Vect* fwd, Vect* up)
//{
//	Instance().listenerPos = pos;
//	Instance().listenerFwd = fwd;
//	Instance().listenerUp = up;
//}

FMOD_RESULT CAudioManager::CreateFMODChannelGroup(FMOD::ChannelGroup** chnlGrp)
{
	return Instance().createFMODChannelGroupInternal(chnlGrp);
}

FMOD_RESULT CAudioManager::createFMODChannelGroupInternal(FMOD::ChannelGroup** chnlGrp)
{
	FMOD_RESULT result;
	result = Instance().sys->createChannelGroup(0, chnlGrp);
	assert(result == FMOD_OK);
	return result;
}

void CAudioManager::Set3DSettings(float dopplerScale, float distanceFactor, float rolloffScale)
{
	FMOD_RESULT result;
	result = Instance().sys->set3DSettings(dopplerScale, distanceFactor, rolloffScale);
	assert(result == FMOD_OK);
}

void CAudioManager::Terminate()
{
	delete CAudioManagerInstance;
	CAudioManagerInstance = nullptr;
}

CAudioManager::~CAudioManager()
{
	FMOD_RESULT result;
	result = Instance().sys->release();
	assert(result == FMOD_OK);
}