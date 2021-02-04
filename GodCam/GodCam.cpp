#include "GodCam.h"
#include "Camera.h"

GodCam::GodCam() : transSpeed(3.0f), rotSpeed(0.03f)
{
};

void GodCam::setTransSpeed(float newSpeed)
{
	transSpeed = newSpeed;
}

void GodCam::setRotSpeed(float newSpeed)
{
	rotSpeed = newSpeed;
}

void GodCam::processGodCam(Camera* cam)
{
	//check for movement
	if (GetKeyState('W') & 0x08000)
	{
		cam->TranslateForwardBack(transSpeed);
	}
	else if (GetKeyState('S') & 0x08000)
	{
		cam->TranslateForwardBack(-transSpeed);
	}

	if (GetKeyState('A') & 0x08000)
	{
		cam->TranslateLeftRight(-transSpeed);
	}
	else if (GetKeyState('D') & 0x08000)
	{
		cam->TranslateLeftRight(transSpeed);
	}

	//check for rotation
	if (GetKeyState(VK_LEFT) & 0x08000)
	{
		cam->RotateLeftRight(rotSpeed);
	}
	else if (GetKeyState(VK_RIGHT) & 0x08000)
	{
		cam->RotateLeftRight(-rotSpeed);
	}

	if (GetKeyState(VK_UP) & 0x08000)
	{
		cam->RotateUpDown(rotSpeed);
	}
	else if (GetKeyState(VK_DOWN) & 0x08000)
	{
		cam->RotateUpDown(-rotSpeed);
	}
	//need to force camera update
	cam->updateCamera();
}