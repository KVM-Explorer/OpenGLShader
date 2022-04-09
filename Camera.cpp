#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera()
{
	viewPos = vec3(0.f, 1.f, 680.f);
	alpha = 170.f;
	beta = 0.f;

	viewHead.y = sin(glm::radians(beta));
	auto r = cos(glm::radians(beta));
	viewHead.x = r * sin(glm::radians(alpha));	// origin is right
	viewHead.z = r * cos(glm::radians(alpha));
	viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));

	viewMode = ViewMode::XY;

}

Camera::~Camera()
{

}

void Camera::init()
{
	viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
}
/*
	屏幕鼠标输入
		注意value的范围应该是屏幕上下界对应180
		注意value的范围应该是平步左右界对应360

*/
void Camera::inputMouse(const unsigned char& key, float value)
{
	using glm::radians;
	float r = 0;
	switch (key)
	{
		case 'W':
			if (beta+value < 90)beta += value; 
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is rightsss
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));

			break;
		case 'S':
			if (beta-value > -90)beta -= value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;

		case 'A':
			
			if (alpha - value > 0) alpha -= value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case 'D':
			
			if (alpha+value < 360)alpha += value;;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		default:
			break;
	}
	
	TRACE("A: %.2f B %.2f\n", alpha, beta);
}

void Camera::inputKeyboard(const unsigned char& key)
{
	float step = 10.f;
	switch (key)
	{
		case 'w':
		case 'W':
		case VK_UP:
			viewPos += step * viewHead;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, vec3(0.f, 1.f, 0.f));
			break;
		case 's':
		case 'S':
		case VK_DOWN:
			viewPos -= step * viewHead;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, vec3(0.f, 1.f, 0.f));
			break;
		case 'a':
		case 'A':
		case VK_LEFT:

			viewPos -= step * glm::normalize(glm::cross(viewHead, vec3(0.f, 1.f, 0.f)));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
			break;
		case 'd':
		case 'D':
		case VK_RIGHT:

			viewPos += step * glm::normalize(glm::cross(viewHead, vec3(0.f, 1.f, 0.f)));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
			break;
		case 'z':
		case 'Z'://抬高相机
			viewPos.y += step;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case 'x':
		case 'X'://降低相机
			viewPos.y -= step;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
	}
	TRACE("Pos %.2f %.2f %.2f \n", viewPos.x,viewPos.y,viewPos.z);
	//TRACE("Direct %.2f %.2f %.2f\n", viewHead.x, viewHead.y, viewHead.z);
}



mat4 Camera::getViewMatrix() const
{
    return viewMatrix;
}


vec3 Camera::getDirection() const
{
    return viewHead;
}

vec3 Camera::getPosition() const
{
    return viewPos;
}

void Camera::setViewMode(ViewMode mode)
{
	viewMode = mode;
	switch (mode)
	{
	case Camera::ViewMode::XY:
		viewPos = vec3(0.f,1.f,680.f);
		alpha = 170.f;
		beta = 0.f;
		break;
	case Camera::ViewMode::XZ:
		viewPos = vec3(45.f, 853.f, 0.f);
		alpha = 171.f;
		beta = -89.f;
		break;
	case Camera::ViewMode::YZ:
		viewPos = vec3(-1052.f, 0.f, -190.f);
		alpha = 71.f;
		beta = 0.f;
		break;
	case Camera::ViewMode::XYZ:
		viewPos = vec3(0.f, 1.f, 680.f);
		alpha = 170.f;
		beta = 0.f;
		break;
	default:
		break;
	}
	viewHead.y = sin(glm::radians(beta));
	auto r = cos(glm::radians(beta));
	viewHead.x = r * sin(glm::radians(alpha));	// origin is right
	viewHead.z = r * cos(glm::radians(alpha));
	viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));

}

Camera::ViewMode Camera::getViewMode() const
{
	return viewMode;
}
