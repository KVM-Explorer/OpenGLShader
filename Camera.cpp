#include "pch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera()
{
	viewPos = vec3(0.f, 1.f, 6.f);

	alpha = 180.f;
	beta = 0.f;
	viewHead.y = 0.f;
	viewHead.x = sin(glm::radians(alpha));	//0
	viewHead.z = cos(glm::radians(alpha));	//-1
}

Camera::~Camera()
{

}

void Camera::Init()
{
	viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
}
/*
	屏幕鼠标输入
		注意value的范围应该是屏幕上下界对应180
		注意value的范围应该是平步左右界对应360

*/
void Camera::InputMouse(unsigned char& key, float value)
{
	float r = 0;
	switch (key)
	{
		case 'U':
			if (beta < 90)beta += value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha);
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));

			break;
		case 'V':
			if (beta > -90)beta -= value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;

		case '[':
			alpha -= value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case ']':
			alpha += value;
			viewHead.y = sin(glm::radians(beta));
			r = cos(glm::radians(beta));
			viewHead.x = r * sin(glm::radians(alpha));	// origin is right
			viewHead.z = r * cos(glm::radians(alpha));
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		default:
			break;
	}
	
}

void Camera::InputKeyboard(unsigned char& key)
{
	float step = 0.2f;
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
			viewPos.y += 1.1f;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
		case 'x':
		case 'X'://降低相机
			viewPos.y -= 1.1f;
			viewMatrix = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
			break;
	}
}



mat4 Camera::GetViewMatrix() const
{
    return viewMatrix;
}

vec3 Camera::GetDirection() const
{
    return viewHead;
}

vec3 Camera::GetPosition() const
{
    return viewPos;
}
