#ifndef C_SOUND_DSP
#define C_SOUND_DSP

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"

class CSoundDSPAttorney;

#include <vector>

class CSoundDSP
{
	friend class CSoundDSPAttorney;
private:
	FMOD::DSP* dsp;
	using DSPList = std::vector<CSoundDSP*>;
	//List of DSPs that feed into this DSP
	DSPList inputList;
	//List of DSPs that this DSP feeds into 
	DSPList outputList;

	//internal list management
	void addDSPToInputList(CSoundDSP* newDSP);
	void addDSPToOutputList(CSoundDSP* newDSP);
	void removeDSPFromInputList(CSoundDSP* newDSP);
	void removeDSPFromOutputList(CSoundDSP* newDSP);

public:
	enum DSPTypes
	{
		Mixer,
		Lowpass,
		Highpass,
		Echo,
		Flange,
		Chorus,
		Tremolo,
		Distortion
	};

	//debug only - for making sure I was setting up my lists properly
	FMOD_DSP_TYPE getFMODDSPType() const;

	//Don't allow a DSP to be created without specifying a type
	CSoundDSP() = delete;
	CSoundDSP(const CSoundDSP&) = delete;
	CSoundDSP& operator=(const CSoundDSP&) = delete;
	~CSoundDSP() = default;

	CSoundDSP(DSPTypes type);

	void addDSPInput(CSoundDSP* newInput);
	void removeDSPInput(CSoundDSP* oldInput);

	CSoundDSP* getDSPInputAtIndex(int index) const;
	CSoundDSP* getDSPOutputAtIndex(int index) const;

	//Returns the number of DSPs that this DSP feeds information to
	int getNumInputs() const;
	//Returns how many DSPs feed information into this DSP
	int getNumOutputs() const;

	//Determines whether or not to activate this DSP and any of its inputs
	void setActive(bool newActive);
	bool getActive() const;

	//Determines whether or not to process this DSP specifically. Processes all inputs regardless
	void setBypass(bool newBypass);
	bool getBypass() const;
};

#endif C_SOUND_DSP