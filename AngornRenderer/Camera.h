#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

const float SPRINGNESS_ROTATION = 175.0f;
const float SPRINGNESS_MOVEMENT = 225.0f;
const float DEFAULT_FOV = 45.0f;
const float DEFAULT_SENSITIVITY = 0.5f;
const float MAX_MOUSE_SENSITIVITY = 0.25f;
const float MIN_MOUSE_SENSITIVITY = 0.05f;
const float CAMERA_BOUND_PI_DIVISOR = 2.2f;
const float MULTIPURPOSE_NUMBER = 15.0f;

class Camera
{
	friend class Renderable;

public:
	Camera(glm::vec3 pos, float nearPlane = 1.0f, float farPlane_ = 15000.0f, float FOV_ = DEFAULT_FOV, glm::vec3 target = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0));
	virtual void Update(float dt);


	void MoveCamera(float dt);
	void RotateCamera(float dt);
	void ComputeCameraMatrices(void);

	float getMouseSensitivity(void) const;
	glm::mat4 getProjectionMtx(void) const;

	bool useMouse_;	// To use mouse input or not

private:
	// Helper functions
	void RotateAnglesAroundVectorUsingQuat(float Angle, float x, float y, float z);
	void SmoothExponentialDecay2D(float dt, float springness, glm::vec2 real, glm::vec2& use);
	void SmoothExponentialDecay3D(float dt, float springness, glm::vec3 real, glm::vec3& use);

	// Camera POSITION and vectors
	glm::vec3 rotation_;
	glm::vec3 position_;
	glm::vec3 target_;
	glm::vec3 up_;
	glm::vec3 view_;
	glm::vec3 right_;

	// Camera matrices
	glm::mat4 viewMat_;
	glm::mat4 projMat_;

	// Perspective
	float nearPlane_;
	float farPlane_;
	float FOV_;
	float ar_;
	float nearPlaneHalfWidth_;
	float nearPlaneHalfHeight_;
	float farPlaneHalfWidth_;
	float farPlaneHalfHeight_;

	// Interpolation
	glm::vec2 mouseDisplacement_;
	glm::vec3 cameraDisplacement_;

	// Sensitivity 
	float sensitivityModifier_;		// Goes from 0 to 1 (0.5 = default sensitivity)


};

#endif
