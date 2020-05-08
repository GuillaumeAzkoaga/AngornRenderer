#include "Camera.h"
#include "InputManager.h"
#include "RenderView.h"
#include "MathUtils.h"


Camera* Camera::instance_ = 0;


void Camera::CreateCamera(glm::vec3 pos, float nearPlane, float farPlane, float FOV)
{
	position_ = pos;
	nearPlane_ = nearPlane;
	farPlane_ = farPlane;
	FOV_ = FOV;
	target_ = glm::vec3(0,0,0);
	up_ = glm::vec3(0,1,0);
	isMouseLocked_ = true;

	// Vectors
	view_ = target_ - position_;
	rotation_ = glm::vec3(0, 0, 0);

	// Camera options
	sensitivityModifier_ = 0.5f;

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
		isMouseLocked_ = !isMouseLocked_;

	if (isMouseLocked_)
	{
		RenderView::getInstance()->setCursorPosition(0, 0);
		RenderView::getInstance()->setCursorVisibility(true);
	}
	else
		RenderView::getInstance()->setCursorVisibility(true);
}

void Camera::MoveCamera(float dt)
{
	glm::vec3 currOffset(0, 0, 0);
	glm::vec3 altView(view_.x, 0.0f, view_.z);

	if (isMouseLocked_)
	{
		// Moves according to input
		if (InputManager::getInstance()->KeyIsPressed('D'))
			currOffset += 15.0f * right_;
		if (InputManager::getInstance()->KeyIsPressed('A'))
			currOffset -= 15.0f * right_;
		if (InputManager::getInstance()->KeyIsPressed('E'))
			currOffset += 15.0f * glm::vec3(0, 1, 0);
		if (InputManager::getInstance()->KeyIsPressed('Q'))
			currOffset -= 15.0f * glm::vec3(0, 1, 0);
		if (InputManager::getInstance()->KeyIsPressed('W'))
			currOffset += 15.0f * altView;
		if (InputManager::getInstance()->KeyIsPressed('S'))
			currOffset -= 15.0f * altView;
		if (InputManager::getInstance()->KeyIsPressed(VK_SHIFT))
			currOffset *= 15.0f;
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

	// This function gets the POSITION of the mouse
	if (isMouseLocked_)	
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
	float mouseSensitivity = MIN_MOUSE_SENSITIVITY + (MAX_MOUSE_SENSITIVITY - MIN_MOUSE_SENSITIVITY) * sensitivityModifier_;
	MouseDirection.x = -(middleScreenCoords.x - (-1) * mouseCoords.x) * mouseSensitivity * dt;
	MouseDirection.y = -(middleScreenCoords.y - (-1) * -mouseCoords.y) * mouseSensitivity * dt;

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
	Axis = glm::normalize(Axis);
	// Store values
	mouseDisplacement_ = MouseDirection;
	// Rotate certain amount around right/left vector
	RotateAnglesAroundVectorUsingQuat(MouseDirection.y, Axis);
	// Rotate certain amount around up vector
	RotateAnglesAroundVectorUsingQuat(MouseDirection.x, glm::vec3(0,1,0));
	// Recompute the target, otherwise you can't imagine how wrong it's going to be
	target_ = position_ + view_;
}

void Camera::ComputeCameraMatrices()
{
	right_ = glm::normalize(right_);
	up_ = glm::normalize(up_);
	view_ = glm::normalize(view_);

	// Computations
	right_ = glm::normalize(glm::cross(view_, glm::vec3(0.0f, 1.0f, 0.0f)));
	up_ = glm::normalize(glm::cross(right_, view_));
	viewMat_ = glm::lookAt(position_, target_, up_);
	projMat_ = glm::perspective(FOV_, ar_, nearPlane_, farPlane_);
}





void Camera::RotateAnglesAroundVectorUsingQuat(float Angle, glm::vec3 vector)
{
	glm::quat temp, quat_view, result;
	temp = vector * sin(Angle / 2);
	temp.w = cos(Angle / 2);

	quat_view.x = view_.x;
	quat_view.y = view_.y;
	quat_view.z = view_.z;
	quat_view.w = 0;

	result = (temp * quat_view) * glm::conjugate(temp);
	view_ = glm::vec3(result.x, result.y, result.z);
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
