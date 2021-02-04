#ifndef C_SOUND_PLAY_COMMAND
#define C_SOUND_PLAY_COMMAND

class CSound;
class CSoundChannel;

#include "CAudioCommandBase.h"

class CSoundPlayCommand : public CAudioCommandBase
{
private:
	CSound* snd;
	bool startPaused;
	CSoundChannel* newChannel;
public:
	virtual void Execute() override;

	CSoundPlayCommand() = delete;
	CSoundPlayCommand(const CSoundPlayCommand&) = delete;
	CSoundPlayCommand& operator=(const CSoundPlayCommand&) = delete;
	~CSoundPlayCommand() = default;

	CSoundPlayCommand(CSound* sound, bool pause, CSoundChannel* channel);

	void setStartPaused(bool newVal);
	void setNewChannel(CSoundChannel* val);
};

#endif C_SOUND_PLAY_COMMAND