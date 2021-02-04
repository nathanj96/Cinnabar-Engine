#ifndef C_SOUND_CHANNEL_GROUP
#define C_SOUND_CHANNEL_GROUP

#include "CSoundChannelBase.h"
#include "Vect.h"

class CSoundChannelGroup : public CSoundChannelBase
{
private:
	FMOD::ChannelGroup* chnlGrp;

	virtual void setVol(float newVol) override;
	virtual void setPause(bool newPaused) override;
	virtual void setPan(float newPan) override;
	virtual void setPitch(float newPitch) override;
	virtual void addDSP(int index, CSoundDSP* dsp) override;
	virtual void removeDSP(CSoundDSP* dsp) override;
	virtual void incVol(float incAmt) override;
	virtual void set3DAttrs(const Vect& pos, const Vect& vel) override;
	virtual void set3D(bool _3D) override;
	virtual void set3DOcclusion(float directOcclusion, float reverbOcclusion) override;
public:
	CSoundChannelGroup();
	CSoundChannelGroup(const CSoundChannelGroup&) = delete;
	CSoundChannelGroup& operator=(const CSoundChannelGroup&) = delete;
	~CSoundChannelGroup();

	virtual float GetVolume() override;
	virtual bool GetPaused() override;
	virtual float GetPitch() override;

	//might need to make private later?
	FMOD::ChannelGroup* getFMODGrp() const;
};

#endif C_SOUND_CHANNEL_GROUP
