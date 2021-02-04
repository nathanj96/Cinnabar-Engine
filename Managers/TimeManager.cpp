#include "TimeManager.h"
#include "../CinnabarEngine.h"
#include "DebugOut.h"

#include "FreezeTime.h"

//for debug msgs
#include <string>
using namespace std;

TimeManager* TimeManager::timeManagerInstance = nullptr;

void TimeManager::Initialize()
{
	Instance().currentTime = getTime();
	Instance().prevTime = getTime();
	Instance().frameTime = 0.0f;
	Instance().timeFreezer = new FreezeTime();
}

void TimeManager::Terminate()
{
	delete Instance().timeFreezer;
	Instance().timeFreezer = nullptr;
	delete timeManagerInstance;
	timeManagerInstance = nullptr;
}

float TimeManager::getTime()
{
	return Instance().currentTime;
}

float TimeManager::getFrameTime()
{
	return Instance().frameTime;
}

void TimeManager::processTime(float sys_time)
{
	Instance().prevTime = Instance().currentTime;

	//uncomment this in order to enable freeze frame
	Instance().currentTime = Instance().timeFreezer->GetTimeInSeconds(sys_time);

	//comment this out in order to enable freeze frame
	//Instance().currentTime = sys_time;
	Instance().frameTime = Instance().currentTime - Instance().prevTime;
}

void TimeManager::printTimeInfo()
{
	//std::string prevTimeDisplay = "Previous time: " + (int)Instance().prevTime + '\n';
	//const char* prevTimeCStr = prevTimeDisplay.c_str();
	//DebugMsg::out(const_cast<char*>(prevTimeCStr));
	//std::string currentTimeDisplay = "Current time: " + (int)Instance().currentTime +'\n';
	//const char* currentTimeCStr = currentTimeDisplay.c_str();
	//DebugMsg::out(const_cast<char*>(currentTimeCStr));
	//std::string frameTimeDisplay = "Frame time: " + '\n';
	//const char* frameTimeCStr = frameTimeDisplay.c_str();
	//DebugMsg::out(const_cast<char*>(frameTimeCStr));
}