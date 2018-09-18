#include "stdafx.h"
#include "3DCamera.h"

//void Camera::UpdateView() {
//
//	//roll can be removed from here. because is not actually used in FPS camera
//	glm::mat4 matRoll = glm::mat4(1.0f);//identity matrix; 
//	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
//	glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix
//
//									   //roll, pitch and yaw are used to store our angles in our class
//	matRoll = glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
//	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
//	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));
//
//	//order matters
//	glm::mat4 rotate = matRoll * matPitch * matYaw;
//
//	glm::mat4 translate = glm::mat4(1.0f);
//	translate = glm::translate(translate, -eyeVector);
//
//	viewMatrix = rotate * translate;
//}
//
////Just return the view matrix
//glm::mat4 Camera::GetViewMatrix() const
//{
//	return viewMatrix;
//}
//
////when we press key
//void Camera::KeyPressed(const unsigned char key)
//{
//	float dx = 0; //how much we strafe on x
//	float dz = 0; //how much we walk on z
//	switch (key)
//	{
//	case 'w':
//	{
//		dz = 2;
//		break;
//	}
//
//	case 's':
//	{
//		dz = -2;
//		break;
//	}
//	case 'a':
//	{
//		dx = -2;
//		break;
//	}
//
//	case 'd':
//	{
//		dx = 2;
//		break;
//	}
//	default:
//		break;
//	}
//
//	//get current view matrix
//	glm::mat4 mat = GetViewMatrix();
//	//row major
//	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
//	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);
//
//	const float speed = 0.12f;//how fast we move
//
//							  //forward vector must be negative to look forward. 
//							  //read :http://in2gpu.com/2015/05/17/view-matrix/
//	eyeVector += (-dz * forward + dx * strafe) * speed;
//
//	//update the view matrix
//	UpdateView();
//}
//
//void Camera::MouseMove(int x, int y, int width, int height)
//{
//	if (isMousePressed == false)
//		return;
//	//always compute delta
//	//mousePosition is the last mouse position
//	glm::vec2 mouse_delta = glm::vec2(x, y) - mousePosition;
//
//	const float mouseX_Sensitivity = 0.25f;
//	const float mouseY_Sensitivity = 0.25f;
//	//note that yaw and pitch must be converted to radians.
//	//this is done in UpdateView() by glm::rotate
//	yaw += mouseX_Sensitivity * mouse_delta.x;
//	pitch += mouseY_Sensitivity * mouse_delta.y;
//
//	mousePosition = glm::vec2(x, y);
//	UpdateView();
//}
//void Camera::MousePressed(int button, int state, int x, int y)
//{
//
//	if (state == GLUT_UP)
//	{
//		isMousePressed = false;
//	}
//	if (state == GLUT_DOWN)
//	{
//		isMousePressed = true;
//		mousePosition.x = x;
//		mousePosition.y = y;
//	}
//}