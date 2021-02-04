#ifndef CAMERA_MANAGER
#define CAMERA_MANAGER

//Forward declaration
class Camera;
class GodCam;


class CameraManager
{
public:
	Camera* getCurrentCamera() const;
	void setCurrentCamera(Camera* newCam);
	Camera* getCurrent2DCamera() const;
	void setCurrent2DCamera(Camera* new2DCam);

	CameraManager() = default;
	CameraManager(const CameraManager&) = default;
	CameraManager& operator=(const CameraManager&) = default;
	~CameraManager();

	void createStartingCamera();
	void createStarting2DCamera();

	void UpdateGodCam();
	void SetGodCamTransSpeed(float newSpeed);
	void SetGodCamRotSpeed(float newSpeed);
private:
	Camera* currentCam;
	Camera* defaultCam;
	Camera* default2DCam;
	Camera* current2DCam;
	GodCam* godCam;
};

#endif CAMERA_MANAGER