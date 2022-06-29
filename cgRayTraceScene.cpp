#include "pch.h"
#include "cgRayTraceScene.h"
#include "pch.h"
#include "cgRayTraceScene.h"
#include "RayTrace.h"

cgRayTraceScene::cgRayTraceScene()
{
}

cgRayTraceScene::~cgRayTraceScene()
{
}
void cgRayTraceScene::Init()
{
	//computerShader.CompileShader("Shader/computer/raytrace.cs");
	//computerShader.Link();

	//
	//glGenTextures(1, &tex);
	//glBindTexture(GL_TEXTURE_2D, tex);
	//glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 256, 256);
}

void cgRayTraceScene::Render()
{
	//computerShader.Use();
	//glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	//glDispatchCompute(16, 16, 1);
	//computerShader.Unuse();

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	for (auto iterator = elementsArray.begin(); iterator != elementsArray.end(); iterator++)
	{
		(*iterator)->Render(projectionMat);
	}
	
}

void cgRayTraceScene::Update()
{
}

void cgRayTraceScene::SetProjection(mat4 projection)
{
	projectionMat = projection;
}

void cgRayTraceScene::SetProjection(int width, int height)
{
}

void cgRayTraceScene::AddElement(std::shared_ptr<cgElement> element)
{
	elementsArray.push_back(element);
}

