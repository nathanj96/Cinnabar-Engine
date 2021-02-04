#include "CSound3DReverb.h"
#include "CAudioManager.h"

CSound3DReverb::CSound3DReverb(ReverbTypes type)
{
	FMOD_RESULT result;
	result = CAudioManager::CreateFMODReverb3D(type, &reverb);
	assert(result == FMOD_OK);
}

void CSound3DReverb::Set3DAttributes(const Vect& pos3D, float beginRad, float endRad)
{
	//because of course FMOD has to have its own vector type...
	FMOD_VECTOR posFMOD;
	posFMOD.x = pos3D.X();
	posFMOD.y = pos3D.Y();
	posFMOD.z = pos3D.Z();
	FMOD_RESULT result;
	result = reverb->set3DAttributes(&posFMOD, beginRad, endRad);
	assert(result == FMOD_OK);
}

void CSound3DReverb::Get3DAttributes(Vect* pos3D, float* beginRad, float* endRad) const
{
	FMOD_VECTOR posFMOD;
	FMOD_RESULT result;
	result = reverb->get3DAttributes(&posFMOD, beginRad, endRad);
	assert(result == FMOD_OK);
	pos3D->set(posFMOD.x, posFMOD.y, posFMOD.z);
}

void CSound3DReverb::setActive(bool newActive)
{
	FMOD_RESULT result;
	result = reverb->setActive(newActive);
	assert(result == FMOD_OK);
}

bool CSound3DReverb::getActive() const
{
	FMOD_RESULT result;
	bool active;
	result = reverb->getActive(&active);
	assert(result == FMOD_OK);
	return active;
}

CSound3DReverb::~CSound3DReverb()
{
	FMOD_RESULT result;
	result = reverb->release();
	assert(result == FMOD_OK);
}