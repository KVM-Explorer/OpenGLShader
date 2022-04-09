#pragma once
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

class Camera
{
public:
	enum class ViewMode
	{
		XY,
		XZ,
		YZ,
		XYZ
	};
protected:
	vec3 viewHead;
	vec3 viewPos;
	mat4 viewMatrix;

	float alpha;
	float beta;

	ViewMode viewMode;

public:
	Camera();
	~Camera();

	void inputMouse(const unsigned char& key, float value);
	void inputKeyboard(const unsigned char& key);
	void init();
	mat4 getViewMatrix() const;
	vec3 getDirection() const;
	vec3 getPosition() const;
	void setViewMode(ViewMode mode);
	ViewMode getViewMode() const;
};

