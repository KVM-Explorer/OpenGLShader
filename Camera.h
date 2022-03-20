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

	void inputMouse(unsigned char& key, float value);
	void inputKeyboard(unsigned char& key);
	void init();
	mat4 getViewMatrix() const;
	vec3 getDirection() const;
	vec3 getPosition() const;
};

