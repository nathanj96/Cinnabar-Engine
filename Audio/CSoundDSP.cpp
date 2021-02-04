#include "CSoundDSP.h"
#include "CAudioManager.h"

//for find
using namespace std;

CSoundDSP::CSoundDSP(DSPTypes type)
{
	FMOD_RESULT result;
	result = CAudioManager::CreateFMODDSP(type, &dsp);
	assert(result == FMOD_OK);
}

void CSoundDSP::addDSPInput(CSoundDSP* newInput)
{
	FMOD_RESULT result;
	result = dsp->addInput(newInput->dsp);
	assert(result == FMOD_OK);
	//internal list management
	addDSPToInputList(newInput);
	newInput->addDSPToOutputList(this);
}

void CSoundDSP::removeDSPInput(CSoundDSP* oldInput)
{
	FMOD_RESULT result;
	result = dsp->disconnectFrom(oldInput->dsp);
	assert(result == FMOD_OK);
	//internal list management
	removeDSPFromInputList(oldInput);
	oldInput->removeDSPFromOutputList(this);
}

void CSoundDSP::addDSPToInputList(CSoundDSP* newDSP)
{
	inputList.push_back(newDSP);
}

void CSoundDSP::addDSPToOutputList(CSoundDSP* newDSP)
{
	outputList.push_back(newDSP);
}

void CSoundDSP::removeDSPFromInputList(CSoundDSP* oldDSP)
{
	DSPList::iterator it = std::find(inputList.begin(), inputList.end(), oldDSP);
	inputList.erase(it);
}

void CSoundDSP::removeDSPFromOutputList(CSoundDSP* oldDSP)
{
	DSPList::iterator it = std::find(outputList.begin(), outputList.end(), oldDSP);
	outputList.erase(it);
}

CSoundDSP* CSoundDSP::getDSPInputAtIndex(int index) const
{
	return inputList[index];
}

CSoundDSP* CSoundDSP::getDSPOutputAtIndex(int index) const
{
	return outputList[index];
}

int CSoundDSP::getNumInputs() const
{
	int inputs;
	FMOD_RESULT result;
	result = dsp->getNumInputs(&inputs);
	assert(result == FMOD_OK);
	return inputs;
}

int CSoundDSP::getNumOutputs() const
{
	int outputs;
	FMOD_RESULT result;
	result = dsp->getNumOutputs(&outputs);
	assert(result == FMOD_OK);
	return outputs;
}

void CSoundDSP::setActive(bool newActive)
{
	FMOD_RESULT result;
	result = dsp->setActive(newActive);
	assert(result == FMOD_OK);
}

bool CSoundDSP::getActive() const
{
	bool active;
	FMOD_RESULT result;
	result = dsp->getActive(&active);
	assert(result == FMOD_OK);
	return active;
}

void CSoundDSP::setBypass(bool newBypass)
{
	FMOD_RESULT result;
	result = dsp->setBypass(newBypass);
	assert(result == FMOD_OK);
}

bool CSoundDSP::getBypass() const
{
	bool bypass;
	FMOD_RESULT result;
	result = dsp->getBypass(&bypass);
	assert(result == FMOD_OK);
	return bypass;
}

FMOD_DSP_TYPE CSoundDSP::getFMODDSPType() const
{
	FMOD_DSP_TYPE type;
	FMOD_RESULT result;
	result = dsp->getType(&type);
	assert(result == FMOD_OK);
	return type;
}

