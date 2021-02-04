////Code for a god cam

#ifndef GOD_CAM
#define GOD_CAM

class Camera;

class GodCam
{
private:
	float transSpeed;
	float rotSpeed;
public:
	GodCam();
	GodCam(const GodCam&) = delete;
	GodCam& operator=(const GodCam&) = delete;
	~GodCam() = default;

	void processGodCam(Camera* cam);

	void setTransSpeed(float newSpeed);
	void setRotSpeed(float newSpeed);
};
#endif GOD_CAM