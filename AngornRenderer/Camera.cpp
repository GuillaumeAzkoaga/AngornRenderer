#include "Camera.h"
#include "InputManager.h"
#include "RenderView.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define PI 3.1415926535897932384626433832795f
#define EPSILON 0.0001f
#define isZero(x) ((x < EPSILON) && (x > -EPSILON)) 

glm::vec3 Normalize(const glm::vec3 & v)
{
	float length = glm::length(v);
	if (isZero(length))
	{
		return glm::vec3(0.0f);
	}

	return v / length;
}

glm::vec4 Normalize(const glm::vec4 & v)
{
	float length = glm::length(v);
	if (isZero(length))
	{
		return glm::vec4(0.0f);
	}

	return v / length;
}


Camera::Camera(glm::vec3 pos, float nearPlane, float farPlane, float FOV, glm::vec3 target, glm::vec3 up) : position_(pos), nearPlane_(nearPlane), farPlane_(farPlane), FOV_(FOV), target_(target), up_(up), useMouse_(true)
{
	// Vectors
	view_ = target_ - position_;
	rotation_ = glm::vec3(0, 0, 0);

	// Camera options
	sensitivityModifier_ = DEFAULT_SENSITIVITY;

	// Interpolation
	mouseDisplacement_ = glm::vec2(0.0f, 0.0f);
	cameraDisplacement_ = glm::vec3(0.0f, 0.0f, 0.0f);

	// Perspective
	ar_ = (float)RenderView::getInstance()->getWidth() / RenderView::getInstance()->getHeight();
	nearPlaneHalfWidth_ = nearPlane_ * glm::tan(glm::radians(FOV_ / 2.0f));
	nearPlaneHalfHeight_ = nearPlaneHalfWidth_ / ar_;
	farPlaneHalfWidth_ = farPlane_ * glm::tan(glm::radians(FOV_ - 0.5f));
	farPlaneHalfHeight_ = farPlaneHalfWidth_ / ar_;
}

void Camera::Update(float dt)
{
	// Manipulating the transform (order is important)
	MoveCamera(dt);
	RotateCamera(dt);

	// Mandatory computation
	ComputeCameraMatrices();

	//TODO: Do this only when the key is triggered, not at each frame...
	if (InputManager::getInstance()->KeyIsTriggered(VK_SPACE))
		useMouse_ = !useMouse_;

	if (useMouse_)
	{
		RenderView::getInstance()->setCursorPosition(0, 0);
		RenderView::getInstance()->setCursorVisibility(true);
	}
	else
		RenderView::getInstance()->setCursorVisibility(false);
}

void Camera::MoveCamera(float dt)
{
	glm::vec3 currOffset(0, 0, 0);
	glm::vec3 altView(view_.x, 0.0f, view_.z);

	if (useMouse_)
	{
		// Moves according to input
		if (InputManager::getInstance()->KeyIsPressed('D'))
			currOffset += MULTIPURPOSE_NUMBER * right_;
		if (InputManager::getInstance()->KeyIsPressed('A'))
			currOffset -= MULTIPURPOSE_NUMBER * right_;
		if (InputManager::getInstance()->KeyIsPressed('E'))
			currOffset += MULTIPURPOSE_NUMBER * glm::vec3(0, 1, 0);
		if (InputManager::getInstance()->KeyIsPressed('Q'))
			currOffset -= MULTIPURPOSE_NUMBER * glm::vec3(0, 1, 0);
		if (InputManager::getInstance()->KeyIsPressed('W'))
			currOffset += MULTIPURPOSE_NUMBER * altView;
		if (InputManager::getInstance()->KeyIsPressed('S'))
			currOffset -= MULTIPURPOSE_NUMBER * altView;
		if (InputManager::getInstance()->KeyIsPressed(VK_SHIFT))
			currOffset *= MULTIPURPOSE_NUMBER;
	}

	// Interpolation
	SmoothExponentialDecay3D(dt, SPRINGNESS_MOVEMENT, cameraDisplacement_, currOffset);
	cameraDisplacement_ = currOffset;

	// Apply result
	position_ += currOffset;
}

void Camera::RotateCamera(float dt)
{
	// the coordinates of our mouse coordinates
	glm::vec2 mouseCoords(0, 0);

	// the middle of the screen in the x and y direction
	glm::vec2 middleScreenCoords(0, 0);


	// vector that describes mousePOSITION - center
	glm::vec2 MouseDirection(0, 0);

	// static variable to store the rotation about the x-axis, since
	// we want to limit how far up or down we can look.
	// We don't need to cap the rotation about the y-axis as we
	// want to be able to turn around 360 degrees
	static double CurrentRotationAboutX = 0.0;

	// The maximum angle we can look up or down, in radians
	double maxAngle = 1;

	// This function gets the POSITION of the mouse
	if (useMouse_)	
		mouseCoords = InputManager::getInstance()->getMousePosition();
	

	// get the distance and direction the mouse moved in x (in
	// pixels). We can't use the actual number of pixels in radians,
	// as only six pixels  would cause a full 360 degree rotation.
	// So we use a mousesensitivity variable that can be changed to
	// vary how many radians we want to turn in the x-direction for
	// a given mouse movement distance.
	// We have to remember that positive rotation is counter-clockwise. 
	// Moving the mouse down is a negative rotation about the x axis
	// Moving the mouse right is a negative rotation about the y axis
	MouseDirection.x = -(middleScreenCoords.x - (-1) * -mouseCoords.x) * getMouseSensitivity() * dt;
	MouseDirection.y = -(middleScreenCoords.y - (-1) * mouseCoords.y) * getMouseSensitivity() * dt;

	// Smooth the movement of the mouse (interpolate)
	SmoothExponentialDecay2D(dt, SPRINGNESS_ROTATION, mouseDisplacement_, MouseDirection);

	// Fix a really strange problem
	float temp_rot_x = rotation_.x;

	// Modify rotation every frame
	rotation_.x += MouseDirection.y;

	// We don't want to rotate up too much, so we cap it.
	if (rotation_.x > PI / CAMERA_BOUND_PI_DIVISOR)
	{
		float tempVal = rotation_.x - PI / CAMERA_BOUND_PI_DIVISOR;
		MouseDirection.y -= tempVal;
		rotation_.x = temp_rot_x + MouseDirection.y;
	}
	// We don't want to rotate down too much, so we cap it.
	if (rotation_.x < -PI / CAMERA_BOUND_PI_DIVISOR)
	{
		float tempVal = rotation_.x + PI / CAMERA_BOUND_PI_DIVISOR;
		MouseDirection.y -= tempVal;
		rotation_.x = temp_rot_x + MouseDirection.y;
	}

	// get the axis to rotate around
	glm::vec3 Axis = glm::cross(view_, up_);
	// To be able to use the quaternion conjugate, the axis to
	// rotate around must be normalized.
	Axis = Normalize(Axis);
	// Store values
	mouseDisplacement_.x = MouseDirection.x;
	mouseDisplacement_.y = MouseDirection.y;
	// Rotate certain amount around right/left vector
	RotateAnglesAroundVectorUsingQuat(MouseDirection.y, Axis.x, Axis.y, Axis.z);
	// Rotate certain amount around up vector
	RotateAnglesAroundVectorUsingQuat(MouseDirection.x, 0, 1, 0);
	// Recompute the target, otherwise you can't imagine how wrong it's going to be
	target_ = position_ + view_;
}

void Camera::ComputeCameraMatrices()
{
	// Sanity
	right_ = Normalize(right_);
	up_ = Normalize(up_);
	view_ = Normalize(view_);

	// Computations
	right_ = Normalize(glm::cross(view_, glm::vec3(0.0f, 1.0f, 0.0f)));
	up_ = Normalize(glm::cross(right_, view_));
	viewMat_ = glm::lookAt(position_, target_, up_);
	projMat_ = glm::perspective(FOV_, ar_, nearPlane_, farPlane_);
}





void Camera::RotateAnglesAroundVectorUsingQuat(float Angle, float x, float y, float z)
{
	glm::quat temp, quat_view, result;

	temp.x = x * sin(Angle / 2);
	temp.y = y * sin(Angle / 2);
	temp.z = z * sin(Angle / 2);
	temp.w = cos(Angle / 2);

	quat_view.x = view_.x;
	quat_view.y = view_.y;
	quat_view.z = view_.z;
	quat_view.w = 0;

	result = (temp * quat_view) * glm::conjugate(temp);

	view_.x = result.x;
	view_.y = result.y;
	view_.z = result.z;
}

void Camera::SmoothExponentialDecay2D(float dt, float springness, glm::vec2 real, glm::vec2& use)
{
	// This is an exponential decay function
	// Get the right value for springness
	// springness = number of times the distance between two values will halve
	float d = 1 - exp(log(0.5f) * springness * dt);
	use += (real - use) * d;
}

void Camera::SmoothExponentialDecay3D(float dt, float springness, glm::vec3 real, glm::vec3& use)
{
	// This is an exponential decay function
	// Get the right value for springness
	// springness = number of times the distance between two values will halve
	float d = 1 - exp(log(0.5f) * springness * dt);
	use += (real - use)*d;
}



///////////////////////////////////////////// GETTORS /////////////////////////////////////////////

float Camera::getMouseSensitivity(void) const
{
	return MIN_MOUSE_SENSITIVITY + (MAX_MOUSE_SENSITIVITY - MIN_MOUSE_SENSITIVITY) * sensitivityModifier_;
}



glm::mat4 Camera::getProjectionMtx() const
{
	return projMat_;
}