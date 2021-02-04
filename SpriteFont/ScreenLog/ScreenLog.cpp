#include "ScreenLog.h"
#include "SpriteFontManager.h"
#include "SpriteString.h"

ScreenLog* ScreenLog::screenLogInstance = nullptr;

void ScreenLog::Initialize()
{
	Instance().anchorX = 8;
	Instance().anchorY = 8;
	Instance().sfont = SpriteFontManager::getSpriteFont("TestFont");
}

void ScreenLog::Terminate()
{
	delete screenLogInstance;
	screenLogInstance = nullptr;
}

void ScreenLog::Render()
{
	SpriteString sprStr(Instance().sfont);
	int currX = Instance().anchorX;
	int currY = Instance().anchorY;
	for (MessagesList::iterator it = Instance().msgList.begin(); it != Instance().msgList.end(); it++)
	{
		sprStr.Set(Instance().sfont, (*it), currX, currY);
		sprStr.Render();
		currY += sprStr.getHeight();
	}
	Instance().msgList.clear();
}

void ScreenLog::Add(char* A, ...)
{
	va_list args;

	va_start(args, A);
	vsprintf_s(Instance().DebugBuff, A, args);
	va_end(args);

	std::string s(Instance().DebugBuff);
	Instance().msgList.push_back(s);
}