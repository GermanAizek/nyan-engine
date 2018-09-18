#pragma once
#include "RenderVulkan.h"

#include <vector>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = float(-90.f);
const float PITCH = float(0.f);
const float SPEED = float(6.f);
const float SENSITIVITY = float(0.25f);
const float ZOOM = float(45.f);

class Camera {
public:
	int IT_ORBIT = 10;
	int X = 0;
	int Y = 0;
	int Z = 0;
	int look_x = 0;
	int look_y = 0;
	int look_z = 0;

	Camera(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW, float pitch = PITCH)
		: front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->pos = pos;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->pos = glm::vec3( posX, posY, posZ );
		this->worldUp = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		this->updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(this->pos, this->pos + this->front, this->up);
	}

	void ProcessKeyboard(Camera_Movement direction, float dtime) {
		float velocity = this->movementSpeed * dtime;

		if (FORWARD == direction) this->pos += this->front * velocity;
		if (BACKWARD == direction) this->pos -= this->front * velocity;
		if (LEFT == direction) this->pos -= this->front * velocity;
		if (RIGHT == direction) this->pos += this->front * velocity;
	}

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true) {
		xOffset *= this->mouseSensitivity;
		yOffset *= this->mouseSensitivity;

		this->yaw += xOffset;
		this->pitch += yOffset;

		if (constrainPitch) {
			if (this->pitch > 89.f) this->pitch = 89.f;
			if (this->pitch < -89.f) this->pitch = -89.f;
		}

		this->updateCameraVectors();
	}

	void ProcessMouseScroll(float yOffset) {
		if (this->zoom >= 1.f && this->zoom <= 45.f) this->zoom -= yOffset;
		if (this->zoom <= 1.f) this->zoom = 1.f;
		if (this->zoom >= 45.f) this->zoom = 45.f;
	}
	float GetZoom() {
		return this->zoom;
	}

private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	void updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};