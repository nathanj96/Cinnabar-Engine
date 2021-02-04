#include "CameraManager.h"
#include "Camera.h"
#include "../CinnabarEngine.h"
#include "GodCam.h"

void CameraManager::createStartingCamera()
{
	Camera* cam = new Camera(Camera::Type::PERSPECTIVE_3D);
	cam->setViewport(0, 0, CinnabarEngine::GetWidth(), CinnabarEngine::GetHeight());
	cam->setPerspective(35.0f, float(CinnabarEngine::GetWidth()) / float(CinnabarEngine::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	cam->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	cam->updateCamera();  // Note: if the camera moves/changes, we need to call update again

	this->defaultCam = cam;
	this->currentCam = cam;
	godCam = new GodCam();
}

void CameraManager::createStarting2DCamera()
{
	Camera* cam2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	assert(cam2D);

	cam2D->setViewport(0, 0, CinnabarEngine::GetWidth(), CinnabarEngine::GetHeight());
	cam2D->setOrthographic(-0.5f * CinnabarEngine::GetWidth(), 0.5f * CinnabarEngine::GetWidth(), -0.5f * CinnabarEngine::GetHeight(), 0.5f * CinnabarEngine::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	cam2D->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	cam2D->updateCamera();  // Again, if we change anythign about the camera, we need to call update again

	this->default2DCam = cam2D;
	this->current2DCam = cam2D;
}

void CameraManager::setCurrentCamera(Camera* newCamera)
{
	currentCam = newCamera;
}

Camera* CameraManager::getCurrentCamera() const
{
	return currentCam;
}

void CameraManager::setCurrent2DCamera(Camera* new2DCamera)
{
	current2DCam = new2DCamera;
}

Camera* CameraManager::getCurrent2DCamera() const
{
	return current2DCam;
}

void CameraManager::UpdateGodCam()
{
	godCam->processGodCam(getCurrentCamera());
}

void CameraManager::SetGodCamTransSpeed(float newSpeed)
{
	godCam->setTransSpeed(newSpeed);
}

void CameraManager::SetGodCamRotSpeed(float newSpeed)
{
	godCam->setRotSpeed(newSpeed);
}

CameraManager::~CameraManager()
{
	delete defaultCam;
	defaultCam = nullptr;
	delete default2DCam;
	default2DCam = nullptr;
	delete godCam;
	godCam = nullptr;
}

