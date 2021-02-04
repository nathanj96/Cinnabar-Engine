#ifndef C_SOUND_COMMAND_BASE
#define C_SOUND_COMMAND_BASE

class CAudioCommandBase
{
public:
	CAudioCommandBase() = default;
	CAudioCommandBase(const CAudioCommandBase&) = default;
	CAudioCommandBase& operator=(const CAudioCommandBase&) = default;
	virtual ~CAudioCommandBase() = default;

	virtual void Execute() = 0;
};

#endif C_SOUND_COMMAND_BASE