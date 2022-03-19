#pragma once
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

class Camera
{
protected:
	vec3 viewHead;
	vec3 viewPos;
	mat4 viewMatrix;

	float alpha;
	float beta;

public:
	Camera();
	~Camera();

	void InputMouse(unsigned char& key, float value);
	void InputKeyboard(unsigned char& key);
	void Init();
	mat4 GetViewMatrix() const;
	vec3 GetDirection() const;
	vec3 GetPosition() const;
};

