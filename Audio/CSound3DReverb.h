//Class for an instance of 3D reverb in CAudio

#include "fmod_studio.hpp"
#include "fmod_studio_common.h"
#include "Vect.h"

#ifndef C_SOUND_3D_REVERB
#define C_SOUND_3D_REVERB

class CSound3DReverb
{
private:
	FMOD::Reverb3D* reverb;
public:

	/**********************************************************************************************//**
	 * \enum	ReverbTypes
	 * \ingroup CSOUNDREVERB
	 * \brief	Available types of reverb to use.
	 **************************************************************************************************/

	enum ReverbTypes
	{
		PaddedCell,
		Auditorium,
		ConcertHall,
		Cave,
		Alley,
		Underwater
	};

	//force reverb creation using a type
	CSound3DReverb() = delete;
	CSound3DReverb(const CSound3DReverb&) = delete;
	CSound3DReverb& operator=(const CSound3DReverb&) = delete;
	~CSound3DReverb();

	/**********************************************************************************************//**
	 * \fn	CSound3DReverb::CSound3DReverb(ReverbTypes type);
	 * \ingroup CSOUNDREVERBMETHODS
	 * \brief	Required constructor for creating a CSoundReverb object.
	 * \param 	type	The type of reverb to use.
	 **************************************************************************************************/

	CSound3DReverb(ReverbTypes type);

	/**********************************************************************************************//**
	 * \fn	void CSound3DReverb::Set3DAttributes(const Vect& pos3D, float beginRad, float endRad);
	 * \ingroup CSOUNDREVERBMETHODS
	 * \brief	Positions the reverb in 3D space, and sets the minimum and maximum radii away from
	 * 			this position that its effects will be heard.
	 *
	 * \param 	pos3D   	New position in 3D space.
	 * \param 	beginRad	The minimum distance away from pos3D that the reverb will be heard.
	 * \param 	endRad  	The maximum distance away from pos3D that the reverb will be heard.
	 **************************************************************************************************/

	void Set3DAttributes(const Vect& pos3D, float beginRad, float endRad);

	/**********************************************************************************************//**
	 * \fn	void CSound3DReverb::Get3DAttributes(Vect* pos3D, float* beginRad, float* endRad) const;
	 * \brief CSOUNDREVERBMETHODS
	 * \brief	Retrieves the position of the reverb in 3D space, as well as the minimum and maximum radii away from
	 *			this position that its effects will be heard.
	 *			
	 * \param [in,out]	pos3D   	The address of a Vect to receive the reverb's position
	 * \param [in,out]	beginRad	The address of a float to receive the reverb's minimum radius.
	 * \param [in,out]	endRad  	The address of a float to receive the reverb's maximum radius.
	 **************************************************************************************************/

	void Get3DAttributes(Vect* pos3D, float* beginRad, float* endRad) const;

	/**********************************************************************************************//**
	 * \fn	void CSound3DReverb::setActive(bool newActive);
	 * \ingroup CSOUNDREVERBMETHODS
	 * \brief	Sets whether the reverb is active or not.
	 *
	 * \param 	newActive	Whether the reverb is active or not.
	 **************************************************************************************************/

	void setActive(bool newActive);

	/**********************************************************************************************//**
	 * \fn	bool CSound3DReverb::getActive() const;
	 * \ingroup CSOUNDREVERBMETHODS
	 * \brief	Retrieves the active state of the reverb.
	 *
	 * \returns	The active state of the reverb.
	 **************************************************************************************************/

	bool getActive() const;
};

#endif C_SOUND_3D_REVERB