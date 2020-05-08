#ifndef CAMERA_H_
#define CAMERA_H_


#include "MathUtils.h"
#include "ISystem.h"

const float SPRINGNESS_ROTATION = 175.0f;
const float SPRINGNESS_MOVEMENT = 225.0f;
const float MAX_MOUSE_SENSITIVITY = 0.25f;
const float MIN_MOUSE_SENSITIVITY = 0.05f;
const float CAMERA_BOUND_PI_DIVISOR = 2.2f;

class Camera : public ISystem
{
public:
	static Camera* getInstance()
	{
		if (!instance_)
			instance_ = new Camera();
		return instance_;
	}

	void CreateCamera(glm::vec3 pos = glm::vec3(-500,0,0), float nearPlane = 1.0f, float farPlane_ = 15000.0f, float FOV_ = 45.f);
	
	void Initialize() {}
	void Update(float dt = 0);
	void Shutdown() {}

	void MoveCamera(float dt);
	void RotateCamera(float dt);
	void ComputeCameraMatrices();

	glm::mat4 getProjectionMtx() const { return projMat_; }
	glm::mat4 getViewMtx() const { return viewMat_; }

	glm::vec3 getPosition() const { return position_; }

private:
	Camera() {}
	static Camera* instance_;

	bool isMouseLocked_ = true;	// To use mouse input or not

	// Helper functions
	void RotateAnglesAroundVectorUsingQuat(float Angle, glm::vec3 vector);
	void SmoothExponentialDecay2D(float dt, float springness, glm::vec2 real, glm::vec2& use);
	void SmoothExponentialDecay3D(float dt, float springness, glm::vec3 real, glm::vec3& use);

	// Camera POSITION and vectors
	glm::vec3 rotation_ = glm::vec3();
	glm::vec3 position_ = glm::vec3();
	glm::vec3 target_ = glm::vec3();
	glm::vec3 up_ = glm::vec3();
	glm::vec3 view_ = glm::vec3();
	glm::vec3 right_ = glm::vec3();

	// Camera matrices
	glm::mat4 viewMat_ = glm::mat4();
	glm::mat4 projMat_ = glm::mat4();

	// Perspective
	float nearPlane_ = 0;
	float farPlane_ = 0;
	float FOV_ = 45.f;
	float ar_ = 0;
	float nearPlaneHalfWidth_ = 0;
	float nearPlaneHalfHeight_ = 0;
	float farPlaneHalfWidth_ = 0;
	float farPlaneHalfHeight_ = 0;

	// Interpolation
	glm::vec2 mouseDisplacement_ = glm::vec2();
	glm::vec3 cameraDisplacement_ = glm::vec3();

	// Sensitivity 
	float sensitivityModifier_ = 0.5f;		// Goes from 0 to 1 (0.5 = default sensitivity)
};

#endif
