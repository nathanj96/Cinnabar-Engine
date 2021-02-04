#ifndef SCREEN_LOG
#define SCREEN_LOG

class SpriteFont;
class ScreenLogAttorney;

#include <list>
#include <string>
using namespace std;

class ScreenLog
{
	friend class ScreenLogAttorney;
private:

	/** \brief	The x position for the first string to begin printing from. */
	int anchorX;
	/** \brief	The y position for the first string to start printing from. */
	int anchorY;
	char DebugBuff[256];


	/** \brief	Which sprite font the printed strings will use. */
	SpriteFont* sfont;

	using MessagesList = std::list<std::string>;
	MessagesList msgList;

	//singleton
	//Singleton setup
	static ScreenLog* screenLogInstance;

	ScreenLog() = default;
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator=(const ScreenLog&) = delete;
	~ScreenLog() = default;

	static ScreenLog& Instance()
	{
		if (!screenLogInstance)
			screenLogInstance = new ScreenLog;

		return *screenLogInstance;
	}

	/**********************************************************************************************//**
	 * \fn	static void ScreenLog::Initialize();
	 * \ingroup SCREENLOGMETHODS
	 * \brief	In this function, put the coordinates of where the ScreenLog should start rendering from,
	 * 			as well as which SpriteFont it should use.
	 * \note <b>DO NOT PUT ANYTHING ELSE INSIDE THIS FUNCTION!</b> The ScreenLog will handle the rest of
	 * 		 its setup internally!
	 **************************************************************************************************/

	static void Initialize();

	/**********************************************************************************************//**
	 * \fn	static void ScreenLog::Terminate();
	 *
	 * \brief	Called on game end. Cleans up heap memory from the Screen Log.
	 **************************************************************************************************/

	static void Terminate();

	/**********************************************************************************************//**
	 * \fn	static void ScreenLog::Render();
	 *
	 * \brief	Internal process for rendering all strings in the list.
	 **************************************************************************************************/

	static void Render();
public:

	/**********************************************************************************************//**
	 * \fn	static void ScreenLog::Add(char* A, ...);
	 * \ingroup SCREENLOGMETHODS
	 * \brief	Adds a string to the render list. The list is cleared after every frame, so to render
	 * 			a string continuously (e.g. to track an object's position), the string will need to
	 * 			be resent every frame.
	 * 			This function has the same formatting options as a printf() call does. For example, to
	 * 			print a float, use
	 * 			/code
	 * 			{
	 * 				float someFloat = 5.0f;
	 * 				ScreenLog::Add("Showing some float: %f", someFloat);
	 * 			}
	 *			/endcode
	 * 			
	 * \param A The string to add to the list.
	 **************************************************************************************************/

	static void Add(char* A, ...);
};

#endif SCREEN_LOG