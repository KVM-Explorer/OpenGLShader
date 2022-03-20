#pragma once
#include "pch.h"
#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;
using glm::radians;

class Unit
{
public:
	enum class Mode
	{
		single,
		smooth,
		isopleth
	};
protected:
	Mode drawMode;

public:
	void Render();
	void SetDrawMode(Mode mode);
};

