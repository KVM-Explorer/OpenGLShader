#include "pch.h"
#include "cgLightCube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgLightCube::cgLightCube() 
{
	textureID = 0;
	scaleRatio = vec3(1.f, 1.f, 1.f);
}

cgLightCube::~cgLightCube()
{
}

void cgLightCube::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3*elementNum);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void cgLightCube::CalculateModelMatrix()
{
	model = glm::translate(centerPosition);
	auto m = glm::scale(scaleRatio);
	model = model * m;
}

void cgLightCube::SetTextureID(unsigned int id)
{
	textureID = id;
}

void cgLightCube::SetScaleRatio(vec3 ratio)
{
	scaleRatio = ratio;
}

unsigned int cgLightCube::GetTextureID()
{
	return textureID;
}
